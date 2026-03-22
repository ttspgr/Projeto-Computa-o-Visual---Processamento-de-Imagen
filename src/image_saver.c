/*
Projeto de Computação Visual - Processamento de Imagens
Professor: André Kishimoto
Turma 07N
Integrantes:
Lucas Zanini da Silva - 10417361
Tiago Teraoka e Sá - 10418485
*/
#include "include/image_saver.h"
#include <SDL3_image/SDL_image.h>
#include <stdio.h>

int save_image(SDL_Surface *surface, const char *out_path) {
  if (!surface || !out_path)
    return -1;

  if (IMG_SavePNG(surface, out_path) == 0) {
    printf("-> Imagem salva com sucesso (%s)!\n", out_path);
    return 0;
  } else {
    printf("-> Erro ao salvar a imagem: %s\n", SDL_GetError());
    return -1;
  }
}
