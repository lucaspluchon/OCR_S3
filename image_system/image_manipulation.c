#ifdef _WIN32
#	include <SDL.h>
#else
#	include <SDL2/SDL.h>
#endif
#include "image_system.h"
#include "color_system.h"

//------------------------------------------------------------------------
//---- OPERATION FUNCTIONS ON IMAGE
//------------------------------------------------------------------------

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

void Image_Threshold(SDL_Surface* image, int threshold)
{
    Uint32 color = 0;
    for (int x = 0; x < image->w; x++)
    {
        for (int y = 0; y < image->h; y++)
        {
            color = SDL_GetPixel32(image,x,y);
            color = Pixel_Treshold(color,threshold);
            SDL_PutPixel32(image,x,y,color);
        }
    }
}

void Image_Convolution(SDL_Surface* image, int matrix[3][3], double factor)
{
    Uint32 color = 0;

    SDL_Surface* image_temp = Image_Copy(image);
    SDL_LockSurface(image_temp);

    for (int x = 0; x < image->w; x++)
    {
        for (int y = 0; y < image->h; y++)
        {
            color = Pixel_Convolution(image_temp,matrix,x,y,factor);
            SDL_PutPixel32(image,x,y,color);
        }
    }

    SDL_UnlockSurface(image_temp);
    SDL_FreeSurface(image_temp);
}

void Image_Median(SDL_Surface* image)
{
    Uint32 color = 0;

    SDL_Surface* image_temp = Image_Copy(image);
    SDL_LockSurface(image_temp);

    for (int x = 0; x < image->w; x++)
    {
        for (int y = 0; y < image->h; y++)
        {
            color = Pixel_Median(image_temp, x, y);
            SDL_PutPixel32(image, x, y, color);
        }
    }

    SDL_UnlockSurface(image_temp);
    SDL_FreeSurface(image_temp);
}

//Apply all the useful correction to the image before bloc detection
void ApplyCorrection(SDL_Surface* image)
{
    int blur[3][3] = {
                        {1,2,1},
                        {2,4,2},
                        {1,2,1},
                    };

    int sharpen[3][3] = {
                        {0,-1,0},
                        {-1,5,-1},
                        {0,-1,0},
                     };

    SDL_LockSurface(image);

    Image_GrayScale(image);

    Image_Convolution(image,blur,0.0625);
    Image_Convolution(image,sharpen,1);

    Image_Threshold(image,125);

    SDL_UnlockSurface(image);
}
