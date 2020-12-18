#include "headers/preprocessing.h"
#include "../useful/builtin.h"
#include "err.h"

Uint32 Pixel_Median(SDL_Surface* image, int x, int y)
{
    int size = 0;

    for (int i = x - 1; i <= x + 1; i++)
    {
        for (int j = y - 1; j <= y + 1; j++)
        {
            if(Pixel_Exist(image, i, j))
            {
                size++;
            }
        }
    }

    int* L = malloc(size*sizeof(int));
    if (L == NULL)
        errx(1,"Not enough memory !");
    int k = 0;
    Uint32 color = 0;
    for (int i = x - 1; i <= x + 1; i++)
    {
        for (int j = y - 1; j <= y + 1; j++)
        {
            if(Pixel_Exist(image, i, j))
            {
                color = SDL_GetPixel32(image, i, j);
                L[k] = Pixel_GetR(color);
                k++;
            }
        }
    }
    int median = CalculMedian(L, size);

    free(L);

    return Pixel_RGBto32(255, median, median, median);
}


void Image_Median(ocr_data* data)
{
    Uint32 color = 0;

    SDL_Surface* image_temp = Image_Copy(data->sdl.image);
    Image_AutoLock(image_temp);

    for (int x = 0; x < data->sdl.image->w; x++)
    {
        for (int y = 0; y < data->sdl.image->h; y++)
        {
            color = Pixel_Median(image_temp, x, y);
            SDL_PutPixel32(data->sdl.image , x, y, color);
        }
    }

    Image_AutoLock(image_temp);
    SDL_FreeSurface(image_temp);
}