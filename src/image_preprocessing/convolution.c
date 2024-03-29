#include "headers/preprocessing.h"

//General function for convolution
Uint32 Pixel_Convolution(SDL_Surface* image,int matrix[3][3], int x, int y, double factor)
{
    Uint32 color = 0;
    double r = 0;
    int k = 0;
    int l = 0;

    for (int i = y - 1; i <= y + 1; i++)
    {
        for (int j = x - 1; j <= x + 1; j++)
        {
            if (Pixel_Exist(image,j,i))
            {
                color = SDL_GetPixel32(image,j,i);
                r += Pixel_GetR(color) * matrix[k][l]* factor;
            }
            l++;
        }
        k++;
        l = 0;
    }

    return Pixel_RGBto32(255,Pixel_absRGB(r),Pixel_absRGB(r),Pixel_absRGB(r));
}

//Apply convolution for each pixels
void Image_Convolution(ocr_data* data, int matrix[3][3], double factor)
{
    Uint32 color;
    SDL_Surface* image_temp = Image_Copy(data->sdl.image);

    Image_AutoLock(image_temp);

    for (int x = 0; x < data->sdl.image->w; x++)
    {
        for (int y = 0; y < data->sdl.image->h; y++)
        {
            color = Pixel_Convolution(image_temp,matrix,x,y,factor);
            SDL_PutPixel32(data->sdl.image,x,y,color);
        }
    }

    Image_AutoLock(image_temp);
    SDL_FreeSurface(image_temp);
}