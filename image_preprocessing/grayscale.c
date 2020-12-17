#include "headers/preprocessing.h"

Uint32 Pixel_Grayscale(Uint32 color)
{
    int r = Pixel_GetR(color);
    int g = Pixel_GetG(color);
    int b = Pixel_GetB(color);
    int gray = (r + g + b) / 3;
    return Pixel_RGBto32(255,gray,gray,gray);
}

void Image_GrayScale(ocr_data* data)
{
    Uint32 color;
    for (int x = 0; x < data->sdl.image->w; x++)
    {
        for (int y = 0; y < data->sdl.image->h; y++)
        {
            color = SDL_GetPixel32(data->sdl.image,x,y);
            color = Pixel_Grayscale(color);
            SDL_PutPixel32(data->sdl.image,x,y,color);
        }
    }
}



