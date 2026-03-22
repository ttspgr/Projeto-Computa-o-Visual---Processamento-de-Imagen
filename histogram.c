#include "include/histogram.h"
#include <math.h>

HistogramData calc_histogram(SDL_Surface *surface) {
  HistogramData hist = {{0}, 0, 0.0f, 0.0f};
  if (!surface)
    return hist;

  int width = surface->w;
  int height = surface->h;
  Uint32 *pixels = (Uint32 *)surface->pixels;
  hist.total_pixels = width * height;

  const SDL_PixelFormatDetails *details =
      SDL_GetPixelFormatDetails(surface->format);
  if (!details)
    return hist;

  for (int i = 0; i < hist.total_pixels; i++) {
    Uint8 r, g, b, a;
    SDL_GetRGBA(pixels[i], details, NULL, &r, &g, &b, &a);
    hist.bins[r]++;
  }

  long long sum_intensities = 0;
  for (int i = 0; i < 256; i++) {
    sum_intensities += (long long)(i * hist.bins[i]);
  }
  hist.mean = (float)sum_intensities / hist.total_pixels;

  float sum_variance = 0.0f;
  for (int i = 0; i < 256; i++) {
    float diff = i - hist.mean;
    sum_variance += (diff * diff) * hist.bins[i];
  }
  hist.std_dev = sqrtf(sum_variance / hist.total_pixels);

  return hist;
}

SDL_Surface *equalize_surface(SDL_Surface *src) {
  if (!src)
    return NULL;

  SDL_Surface *dst = SDL_ConvertSurface(src, src->format);
  if (!dst)
    return NULL;

  HistogramData hist = calc_histogram(src);

  int cdf[256];
  cdf[0] = hist.bins[0];
  for (int i = 1; i < 256; i++) {
    cdf[i] = cdf[i - 1] + hist.bins[i];
  }

  int cdf_min = 0;
  for (int i = 0; i < 256; i++) {
    if (cdf[i] > 0) {
      cdf_min = cdf[i];
      break;
    }
  }

  Uint8 map[256];
  float denominator = (float)(hist.total_pixels - cdf_min);
  if (denominator == 0.0f)
    denominator = 1.0f;

  for (int i = 0; i < 256; i++) {
    float val = (((float)cdf[i] - cdf_min) / denominator) * 255.0f;
    if (val < 0.0f)
      val = 0.0f;
    if (val > 255.0f)
      val = 255.0f;
    map[i] = (Uint8)roundf(val);
  }

  Uint32 *dst_pixels = (Uint32 *)dst->pixels;
  const SDL_PixelFormatDetails *details =
      SDL_GetPixelFormatDetails(dst->format);

  for (int i = 0; i < hist.total_pixels; i++) {
    Uint8 r, g, b, a;
    SDL_GetRGBA(dst_pixels[i], details, NULL, &r, &g, &b, &a);

    Uint8 new_val = map[r];
    dst_pixels[i] = SDL_MapRGBA(details, NULL, new_val, new_val, new_val, a);
  }

  return dst;
}
