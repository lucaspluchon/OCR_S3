#include "include_ocr.h"

//Show image in a SDL window
void ShowImage(SDL_Surface * image, SDL_Window* window)
{
	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

SDL_Surface* LoadImage(char* path)
{
    if (!FileExist(path))
    {
        exit(1);
    }

    return SDL_LoadBMP(path);
}

void SDL_PutPixel32(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    Uint8 *p = (Uint8*)surface->pixels + y * surface->pitch + x * 4;
    *(Uint32*)p = pixel;
}

Uint32 SDL_GetPixel32(SDL_Surface *surface, int x, int y)
{
    Uint8 *p = (Uint8*)surface->pixels + y * surface->pitch + x * 4;
    return *(Uint32*)p;
}


//Apply all the useful correction to the image for the neural network
void ApplyCorrection(SDL_Surface* image)
{
    SDL_LockSurface(image);

    int averageGray = 0;

    for (int x = 0; x < image->w; x++)
    {
        for (int y = 0; y < image->h; y++)
        {
            Uint32 color = SDL_GetPixel32(image,x,y);
            color = GrayScale_Pixel(color);
            averageGray += getR(color);
            SDL_PutPixel32(image,x,y,color);
        }
    }

    averageGray /= image->w * image->h;

    
    for (int x = 0; x < image->w; x++)
    {
        for (int y = 0; y < image->h; y++)
        {
            Uint32 color = SDL_GetPixel32(image,x,y);
            color = Threshold_Pixel(color,averageGray);
            SDL_PutPixel32(image,x,y,color);
        }
    }

    SDL_UnlockSurface(image);
}

