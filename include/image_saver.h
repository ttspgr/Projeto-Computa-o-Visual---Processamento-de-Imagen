#ifndef IMAGE_SAVER_H
#define IMAGE_SAVER_H

#include <SDL3/SDL.h>

int save_image(SDL_Surface* surface, const char* out_path);

#endif // IMAGE_SAVER_H
