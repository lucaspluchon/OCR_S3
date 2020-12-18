#include "headers/preprocessing.h"


/*
 This file contains :
    - Threshold for a pixel
    - Otsu automatic binarization
    - Image binarization
*/

Uint32 Pixel_Threshold(Uint32 color, int threshold)
{
    int gray = Pixel_GetR(color);
    if (gray <= threshold)
        return Pixel_RGBto32(255,0,0,0);
    return Pixel_RGBto32(255,255,255,255);
}


//Useful function for Otsu Binarization
int* Image_GetHistogram(SDL_Surface* image)
{
    int *histogram = calloc(256, sizeof(int));
    Uint32 color;
    for (int x = 0; x < image->w; x++)
    {
        for (int y = 0; y < image->h; y++)
        {
            color = SDL_GetPixel32(image, x, y);
            histogram[Pixel_GetR(color)]++;
        }
    }
    return histogram;
}

//Return the Thresold to apply on the image
int Image_GetThreshold(SDL_Surface* image)
{
    int threshold = 0;
    double current_max = 0.;
    int sum = 0;
    int sum_background = 0;
    int weight_background = 0;
    int nb_pixels = image->h * image->w;

    int* histogram = Image_GetHistogram(image);
    for (int i = 0; i < 256; i++)
        sum += i * histogram[i];

    for (int i = 0; i < 256; i++)
    {
        weight_background += histogram[i];
        int weight_foreground = nb_pixels - weight_background;
        if (weight_background == 0 || weight_foreground == 0)
            continue;

        sum_background += i * histogram[i];
        int sum_foreground = sum - sum_background;

        double f_weight_background = weight_background;
        double f_weight_foreground = weight_foreground;
        double mean_background = sum_background / f_weight_background;
        double mean_foreground = sum_foreground / f_weight_foreground;
        double mean_diff = mean_background - mean_foreground;

        double variance = f_weight_background *
                          f_weight_foreground *
                          mean_diff * mean_diff;
        if (variance > current_max)
        {
            current_max = variance;
            threshold = i;
        }
    }

    free(histogram);
    return threshold;
}

//General image Threshold
void Image_Threshold(ocr_data* data, int threshold)
{
    Uint32 color;
    int threshold_temp = threshold;

    SDL_Surface* image_temp = Image_Copy(data->sdl.image);
    Image_AutoLock(image_temp);

    if (threshold == -1)
        threshold_temp = Image_GetThreshold(data->sdl.image);

    for (int x = 0; x < data->sdl.image->w; x++)
    {
        for (int y = 0; y < data->sdl.image->h; y++)
        {
            color = SDL_GetPixel32(data->sdl.image,x,y);
            color = Pixel_Threshold(color,threshold_temp);
            SDL_PutPixel32(data->sdl.image,x,y,color);
        }
    }
    Image_AutoLock(image_temp);
    SDL_FreeSurface(image_temp);
}