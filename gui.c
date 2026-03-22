#include "include/gui.h"
#include "include/histogram.h"
#include "include/image_saver.h"
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>

int run_gui(SDL_Surface *original_surface, SDL_Surface *processing_surface) {
  int win_width = processing_surface->w;
  int win_height = processing_surface->h;

  SDL_Window *window_main = SDL_CreateWindow("Proj1 - Processamento de Imagens",
                                             win_width, win_height, 0);
  if (!window_main) {
    printf("Erro ao criar a janela principal: %s\n", SDL_GetError());
    return 1;
  }

  int side_win_width = 300;
  int side_win_height = 500;
  SDL_Window *window_side = SDL_CreateWindow(
      "Histograma e Controles", side_win_width, side_win_height, 0);
  if (!window_side) {
    printf("Erro ao criar a janela secundaria: %s\n", SDL_GetError());
    SDL_DestroyWindow(window_main);
    return 1;
  }

  SDL_SetWindowPosition(window_main, SDL_WINDOWPOS_CENTERED,
                        SDL_WINDOWPOS_CENTERED);
  int main_x, main_y;
  SDL_GetWindowPosition(window_main, &main_x, &main_y);
  SDL_SetWindowPosition(window_side, main_x + win_width + 10, main_y);

  SDL_Renderer *renderer_main = SDL_CreateRenderer(window_main, NULL);
  SDL_Renderer *renderer_side = SDL_CreateRenderer(window_side, NULL);

  SDL_Texture *texture_original =
      SDL_CreateTextureFromSurface(renderer_main, processing_surface);
  SDL_Texture *texture_equalized = NULL;
  SDL_Surface *equalized_surface = NULL;

  bool is_equalized = false;
  SDL_Surface *current_main_surface = processing_surface;
  SDL_Texture *current_main_texture = texture_original;

  SDL_FRect btn_rect = {22.0f, 380.0f, 256.0f, 35.0f};
  bool btn_hover = false;
  bool btn_clicked = false;

  bool is_running = true;
  SDL_Event event;

  while (is_running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        is_running = false;
      } else if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
        is_running = false;
      } else if (event.type == SDL_EVENT_KEY_DOWN) {
        if (event.key.key == SDLK_S) {
          save_image(current_main_surface, "output_image.png");
        }
      } else if (event.type == SDL_EVENT_MOUSE_MOTION) {
        if (event.motion.windowID == SDL_GetWindowID(window_side)) {
          float mx = event.motion.x;
          float my = event.motion.y;
          if (mx >= btn_rect.x && mx <= btn_rect.x + btn_rect.w &&
              my >= btn_rect.y && my <= btn_rect.y + btn_rect.h) {
            btn_hover = true;
          } else {
            btn_hover = false;
            btn_clicked = false;
          }
        }
      } else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        if (event.button.windowID == SDL_GetWindowID(window_side)) {
          if (event.button.button == SDL_BUTTON_LEFT && btn_hover) {
            btn_clicked = true;
          }
        }
      } else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
        if (event.button.windowID == SDL_GetWindowID(window_side)) {
          if (event.button.button == SDL_BUTTON_LEFT && btn_clicked) {
            btn_clicked = false;

            is_equalized = !is_equalized;

            if (is_equalized) {
              if (!equalized_surface) {
                equalized_surface = equalize_surface(processing_surface);
                texture_equalized = SDL_CreateTextureFromSurface(
                    renderer_main, equalized_surface);
              }
              current_main_surface = equalized_surface;
              current_main_texture = texture_equalized;
            } else {
              current_main_surface = processing_surface;
              current_main_texture = texture_original;
            }
          }
        }
      }
    }

    SDL_SetRenderDrawColor(renderer_main, 0, 0, 0, 255);
    SDL_RenderClear(renderer_main);

    SDL_FRect dest_rect = {0.0f, 0.0f, (float)win_width, (float)win_height};
    SDL_RenderTexture(renderer_main, current_main_texture, NULL, &dest_rect);
    SDL_RenderPresent(renderer_main);

    SDL_SetRenderDrawColor(renderer_side, 240, 240, 240, 255);
    SDL_RenderClear(renderer_side);

    int hist_x = 22;
    int hist_y = 200;
    int max_freq = 0;

    HistogramData h_data = calc_histogram(current_main_surface);

    for (int i = 0; i < 256; i++) {
      if (h_data.bins[i] > max_freq)
        max_freq = h_data.bins[i];
    }

    if (max_freq > 0) {
      SDL_SetRenderDrawColor(renderer_side, 50, 50, 200, 255);

      for (int i = 0; i < 256; i++) {
        float bar_height = ((float)h_data.bins[i] / max_freq) * 150.0f;
        SDL_RenderLine(renderer_side, hist_x + i, hist_y, hist_x + i,
                       hist_y - bar_height);
      }
    }

    const char *int_class =
        h_data.mean < 85 ? "Escura" : (h_data.mean < 170 ? "Media" : "Clara");
    const char *con_class = h_data.std_dev < 30
                                ? "Baixo"
                                : (h_data.std_dev < 70 ? "Medio" : "Alto");

    char text_buffer[256];
    SDL_Color text_color = {0, 0, 0, 255};

    TTF_Font *font = TTF_OpenFont("src/arial.ttf", 16);
    if (font) {
      SDL_Surface *txt_surf_1 = TTF_RenderText_Blended(
          font, "--- Analise do Histograma ---", 0, text_color);
      SDL_Texture *txt_tex_1 =
          SDL_CreateTextureFromSurface(renderer_side, txt_surf_1);
      SDL_FRect dest_1 = {22.0f, 230.0f, (float)txt_surf_1->w,
                          (float)txt_surf_1->h};
      SDL_RenderTexture(renderer_side, txt_tex_1, NULL, &dest_1);
      SDL_DestroySurface(txt_surf_1);
      SDL_DestroyTexture(txt_tex_1);

      sprintf(text_buffer, "Intensidade (Media): %.1f", h_data.mean);
      SDL_Surface *txt_surf_2 =
          TTF_RenderText_Blended(font, text_buffer, 0, text_color);
      SDL_Texture *txt_tex_2 =
          SDL_CreateTextureFromSurface(renderer_side, txt_surf_2);
      SDL_FRect dest_2 = {22.0f, 260.0f, (float)txt_surf_2->w,
                          (float)txt_surf_2->h};
      SDL_RenderTexture(renderer_side, txt_tex_2, NULL, &dest_2);
      SDL_DestroySurface(txt_surf_2);
      SDL_DestroyTexture(txt_tex_2);

      sprintf(text_buffer, "Classificacao: %s", int_class);
      SDL_Surface *txt_surf_3 =
          TTF_RenderText_Blended(font, text_buffer, 0, text_color);
      SDL_Texture *txt_tex_3 =
          SDL_CreateTextureFromSurface(renderer_side, txt_surf_3);
      SDL_FRect dest_3 = {22.0f, 285.0f, (float)txt_surf_3->w,
                          (float)txt_surf_3->h};
      SDL_RenderTexture(renderer_side, txt_tex_3, NULL, &dest_3);
      SDL_DestroySurface(txt_surf_3);
      SDL_DestroyTexture(txt_tex_3);

      sprintf(text_buffer, "Constraste (D.P): %.1f", h_data.std_dev);
      SDL_Surface *txt_surf_4 =
          TTF_RenderText_Blended(font, text_buffer, 0, text_color);
      SDL_Texture *txt_tex_4 =
          SDL_CreateTextureFromSurface(renderer_side, txt_surf_4);
      SDL_FRect dest_4 = {22.0f, 320.0f, (float)txt_surf_4->w,
                          (float)txt_surf_4->h};
      SDL_RenderTexture(renderer_side, txt_tex_4, NULL, &dest_4);
      SDL_DestroySurface(txt_surf_4);
      SDL_DestroyTexture(txt_tex_4);

      sprintf(text_buffer, "Classificacao: %s", con_class);
      SDL_Surface *txt_surf_5 =
          TTF_RenderText_Blended(font, text_buffer, 0, text_color);
      SDL_Texture *txt_tex_5 =
          SDL_CreateTextureFromSurface(renderer_side, txt_surf_5);
      SDL_FRect dest_5 = {22.0f, 345.0f, (float)txt_surf_5->w,
                          (float)txt_surf_5->h};
      SDL_RenderTexture(renderer_side, txt_tex_5, NULL, &dest_5);
      SDL_DestroySurface(txt_surf_5);
      SDL_DestroyTexture(txt_tex_5);

      if (btn_clicked) {
        SDL_SetRenderDrawColor(renderer_side, 30, 30, 150, 255);
      } else if (btn_hover) {
        SDL_SetRenderDrawColor(renderer_side, 100, 100, 255, 255);
      } else {
        SDL_SetRenderDrawColor(renderer_side, 50, 50, 200, 255);
      }
      SDL_RenderFillRect(renderer_side, &btn_rect);

      SDL_Color btn_text_color = {255, 255, 255, 255};
      const char *btn_text = is_equalized ? "Ver original" : "Equalizar";
      SDL_Surface *txt_surf_btn =
          TTF_RenderText_Blended(font, btn_text, 0, btn_text_color);
      SDL_Texture *txt_tex_btn =
          SDL_CreateTextureFromSurface(renderer_side, txt_surf_btn);

      float txt_x = btn_rect.x + (btn_rect.w - txt_surf_btn->w) / 2.0f;
      float txt_y = btn_rect.y + (btn_rect.h - txt_surf_btn->h) / 2.0f;
      SDL_FRect dest_btn = {txt_x, txt_y, (float)txt_surf_btn->w,
                            (float)txt_surf_btn->h};

      SDL_RenderTexture(renderer_side, txt_tex_btn, NULL, &dest_btn);
      SDL_DestroySurface(txt_surf_btn);
      SDL_DestroyTexture(txt_tex_btn);

      TTF_CloseFont(font);
    } else {
      printf("Erro ao carregar fonte: %s\n", SDL_GetError());
    }

    SDL_RenderPresent(renderer_side);

    SDL_Delay(16);
  }

  if (texture_equalized)
    SDL_DestroyTexture(texture_equalized);
  if (equalized_surface)
    SDL_DestroySurface(equalized_surface);
  SDL_DestroyTexture(texture_original);
  SDL_DestroyRenderer(renderer_side);
  SDL_DestroyRenderer(renderer_main);
  SDL_DestroyWindow(window_side);
  SDL_DestroyWindow(window_main);

  return 0;
}
