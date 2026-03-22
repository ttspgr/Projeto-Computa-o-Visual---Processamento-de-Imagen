/*
Projeto de Computação Visual - Processamento de Imagens
Professor: André Kishimoto
Turma 07N
Integrantes:
Lucas Zanini da Silva - 10417361
Tiago Teraoka e Sá - 10418485
*/
#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H

#include <SDL3/SDL.h>

// Valida a extensão e carrega a imagem
SDL_Surface* load_image(const char* image_path);

#endif // IMAGE_LOADER_H
