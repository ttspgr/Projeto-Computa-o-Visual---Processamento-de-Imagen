#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

#include "include/grayscale.h"
#include "include/gui.h"
#include "include/image_loader.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Uso: %s <caminho_da_imagem.ext>\n", argv[0]);
    return 1;
  }

  const char *image_path = argv[1];

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    printf("Erro ao inicializar SDL: %s\n", SDL_GetError());
    return 1;
  }

  if (!TTF_Init()) {
    printf("Erro ao inicializar SDL_ttf: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  // Serviço 1: Carregamento
  SDL_Surface *original_surface = load_image(image_path);
  if (!original_surface) {
    TTF_Quit();
    SDL_Quit();
    return 1;
  }

  // Serviço 2: Análise e Conversão
  SDL_Surface *processing_surface =
      convert_to_standard_format(original_surface);
  if (processing_surface) {
    process_grayscale(processing_surface);
  } else {
    printf("Erro: Nao foi possivel converter a imagem para ser processada!\n");
  }

  // Serviços 3 e 4 e 5: Interface Gráfica e Eventos
  if (processing_surface) {
    run_gui(original_surface, processing_surface);
  }

  if (processing_surface)
    SDL_DestroySurface(processing_surface);
  if (original_surface)
    SDL_DestroySurface(original_surface);

  TTF_Quit();
  SDL_Quit();

  return 0;
}
