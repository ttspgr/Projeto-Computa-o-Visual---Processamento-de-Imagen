/*
Projeto de Computação Visual - Processamento de Imagens
Professor: André Kishimoto
Turma 07N
Integrantes:
Lucas Zanini da Silva - 10417361
Tiago Teraoka e Sá - 10418485
*/
#ifndef IMAGE_SAVER_H
#define IMAGE_SAVER_H

#include <SDL3/SDL.h>

int save_image(SDL_Surface* surface, const char* out_path);

#endif // IMAGE_SAVER_H
