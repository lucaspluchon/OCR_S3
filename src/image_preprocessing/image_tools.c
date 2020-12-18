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
    SDL_Surface* res = SDL_ConvertSurface(image, format, 0);
    SDL_FreeFormat(format);
    return res;
}

//Generate a w*h white image
SDL_Surface* Image_Generate(int w, int h)
{
    SDL_PixelFormat *format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);
    SDL_Surface* image = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
    Uint32 color = SDL_MapRGB(format, 255, 255 ,255);
    SDL_FillRect(image, 0, color);

    SDL_FreeFormat(format);
    return image;
}

//Lock automatically the image to modify it
void Image_AutoLock(SDL_Surface* image)
{
    if (SDL_MUSTLOCK(image))
    {
        if (image->locked)
        {
            SDL_UnlockSurface(image);
        }
        else
        {
            SDL_LockSurface(image);
        }
    }
}




