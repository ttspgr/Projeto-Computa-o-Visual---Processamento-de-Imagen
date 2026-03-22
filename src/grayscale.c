/*
Projeto de Computação Visual - Processamento de Imagens
Professor: André Kishimoto
Turma 07N
Integrantes:
Lucas Zanini da Silva - 10417361
Tiago Teraoka e Sá - 10418485
*/
#include "include/grayscale.h"
#include <stdbool.h>
#include <stdio.h>

SDL_Surface *convert_to_standard_format(SDL_Surface *src) {
  if (!src)
    return NULL;
  return SDL_ConvertSurface(src, SDL_PIXELFORMAT_ARGB8888);
}

void process_grayscale(SDL_Surface *surface) {
  if (!surface)
    return;

  bool is_already_grayscale = true;
  int width = surface->w;
  int height = surface->h;
  Uint32 *pixels = (Uint32 *)surface->pixels;

  const SDL_PixelFormatDetails *details =
      SDL_GetPixelFormatDetails(surface->format);
  if (!details) {
    printf("Erro: Nao foi possivel obter os detalhes de formato do pixel.\n");
    return;
  }

  for (int i = 0; i < width * height; i++) {
    Uint8 r, g, b, a;
    SDL_GetRGBA(pixels[i], details, NULL, &r, &g, &b, &a);

    if (r != g || g != b) {
      is_already_grayscale = false;
    }

    // Formula fornecida
    Uint8 y = (Uint8)((0.2125f * r) + (0.7154f * g) + (0.0721f * b));

    pixels[i] = SDL_MapRGBA(details, NULL, y, y, y, a);
  }

  if (is_already_grayscale) {
    printf(" -> A imagem inicial ja estava em escala de cinza. Cores "
           "normalizadas.\n");
  } else {
    printf(" -> A imagem inicial e colorida. Convertida para escala de cinza "
           "com sucesso.\n");
  }
}
