#ifndef GRAYSCALE_H
#define GRAYSCALE_H

#include <SDL3/SDL.h>

SDL_Surface* convert_to_standard_format(SDL_Surface* src);
void process_grayscale(SDL_Surface* surface);

#endif // GRAYSCALE_H
