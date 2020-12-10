#include "headers/preprocessing.h"

void Image_ApplyCorrection(SDL_Surface* image, int threshold, double angle)
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
    Image_Threshold(image,threshold);
    if (angle != -1.)
        Image_Rotate(image,angle);
    SDL_UnlockSurface(image);
}