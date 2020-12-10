#include "headers/preprocessing.h"


Uint32 Pixel_Threshold(Uint32 color, int threshold)
{
    int gray = Pixel_GetR(color);
    if (gray <= threshold)
        return Pixel_RGBto32(255,0,0,0);
    return Pixel_RGBto32(255,255,255,255);
}

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

    return threshold;
}

void Image_Threshold(SDL_Surface* image, int threshold)
{
    Uint32 color;
    int threshold_temp = threshold;

    SDL_Surface* image_temp = Image_Copy(image);
    SDL_LockSurface(image_temp);

    if (threshold == -1)
        threshold_temp = Image_GetThreshold(image);

    for (int x = 0; x < image->w; x++)
    {
        for (int y = 0; y < image->h; y++)
        {
            color = SDL_GetPixel32(image,x,y);
            color = Pixel_Threshold(color,threshold_temp);
            SDL_PutPixel32(image,x,y,color);
        }
    }
    SDL_UnlockSurface(image_temp);
    SDL_FreeSurface(image_temp);
}