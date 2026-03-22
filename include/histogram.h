/*
Projeto de Computação Visual - Processamento de Imagens
Professor: André Kishimoto
Turma 07N
Integrantes:
Lucas Zanini da Silva - 10417361
Tiago Teraoka e Sá - 10418485
*/
#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <SDL3/SDL.h>

typedef struct {
    int bins[256];
    int total_pixels;
    float mean;
    float std_dev;
} HistogramData;

HistogramData calc_histogram(SDL_Surface* surface);
SDL_Surface* equalize_surface(SDL_Surface* src);

#endif // HISTOGRAM_H
