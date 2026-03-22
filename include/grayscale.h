/*
Projeto de Computação Visual - Processamento de Imagens
Professor: André Kishimoto
Turma 07N
Integrantes:
Lucas Zanini da Silva - 10417361
Tiago Teraoka e Sá - 10418485
*/
#ifndef GRAYSCALE_H
#define GRAYSCALE_H

#include <SDL3/SDL.h>

SDL_Surface* convert_to_standard_format(SDL_Surface* src);
void process_grayscale(SDL_Surface* surface);

#endif // GRAYSCALE_H
