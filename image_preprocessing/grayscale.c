#include "headers/preprocessing.h"

Uint32 Pixel_Grayscale(Uint32 color)
{
    int r = Pixel_GetR(color);
    int g = Pixel_GetG(color);
    int b = Pixel_GetB(color);
    int gray = (r + g + b) / 3;
    return Pixel_RGBto32(255,gray,gray,gray);
}

void Image_GrayScale(SDL_Surface* image)
{
    Uint32 color = 0;
    for (int x = 0; x < image->w; x++)
    {
        for (int y = 0; y < image->h; y++)
        {
            color = SDL_GetPixel32(image,x,y);
            color = Pixel_Grayscale(color);
            SDL_PutPixel32(image,x,y,color);
        }
    }
}



