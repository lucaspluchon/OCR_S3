#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include "../useful/builtin.h"
#include "headers/preprocessing.h"


void Image_ToRenderer(SDL_Surface * image, SDL_Renderer* renderer)
{
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
}

SDL_Surface* Image_Load(char* path)
{
    if (!FileExist(path))
    {
        exit(1);
    }

    return IMG_Load(path);
}

SDL_Surface* Image_Copy(SDL_Surface* image)
{
    SDL_PixelFormat *format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);
    return SDL_ConvertSurface(image, format, 0);
}





