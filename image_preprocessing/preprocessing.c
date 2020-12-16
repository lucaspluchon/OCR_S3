#include "headers/preprocessing.h"
#include "../ui/ui.h"

void Image_ApplyCorrection(ocr_data* data)
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
    SDL_LockSurface(data->sdl.image);
    Image_GrayScale(data);
    Image_Convolution(data,blur,0.0625);
    Image_Convolution(data,sharpen,1);
    //Progress_Set(data->ui.progress_main,0.2,data);
    Image_Threshold(data,data->sdl.threshold);
    //Progress_Set(data->ui.progress_main,0.3,data);
    if (data->sdl.angle != -1.)
        Image_Rotate(data,data->sdl.angle);
    SDL_UnlockSurface(data->sdl.image);
}