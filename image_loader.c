#include "include/image_loader.h"
#include <SDL3_image/SDL_image.h>
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#define strcasecmp _stricmp
#endif

SDL_Surface *load_image(const char *image_path) {
  if (!image_path)
    return NULL;

  // Verificacao de extensao pre-load (apenas as exigidas no doc: png, jpeg,
  // jpg, bmp)
  const char *ext = strrchr(image_path, '.');
  if (!ext || (strcasecmp(ext, ".png") != 0 && strcasecmp(ext, ".jpg") != 0 &&
               strcasecmp(ext, ".jpeg") != 0 && strcasecmp(ext, ".bmp") != 0)) {
    printf("Erro: Formato nao permitido. Os suportados sao apenas .png, .jpg e "
           ".bmp\n");
    return NULL;
  }

  printf("Tentando carregar a imagem suportada: %s\n", image_path);

  SDL_Surface *original_surface = IMG_Load(image_path);
  if (!original_surface) {
    printf("Erro: Arquivo nao encontrado ou formato de imagem invalido: %s\n",
           image_path);
    return NULL;
  }

  printf("Imagem '%s' carregada com sucesso! Dimensoes: %d x %d pixels.\n",
         image_path, original_surface->w, original_surface->h);

  return original_surface;
}
