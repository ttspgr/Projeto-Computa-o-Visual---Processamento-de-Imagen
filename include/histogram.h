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
