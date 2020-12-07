#include <stdlib.h>
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

    return SDL_LoadBMP(path);
}

SDL_Surface* Image_Copy(SDL_Surface* image)
{
    return SDL_ConvertSurface(image, image->format, SDL_SWSURFACE);
}





