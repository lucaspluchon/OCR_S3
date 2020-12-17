#include "headers/preprocessing.h"

/*
 Image rotation
    - Not automatically because the results was not great
    - Angle is in degrees
*/

void Image_Rotate(ocr_data* data, double angle)
{
    Uint32 color;
    double xp;
    double yp;
    angle = angle * M_PI / 180;
    double cos_angle = cos(angle);
    double sin_angle = sin(angle);
    int center_x = (int) data->sdl.image->w / 2;
    int center_y = (int) data->sdl.image->h / 2;

    SDL_Surface* image_temp = Image_Copy(data->sdl.image);
    SDL_LockSurface(image_temp);

    for (int x = 0; x < data->sdl.image->w; x++)
    {
        for (int y = 0; y < data->sdl.image->h; y++)
        {
            xp = (x - center_x) * cos_angle - (y - center_y) * sin_angle + center_x;
            yp = (x - center_x) * sin_angle + (y - center_y) * cos_angle + center_y;
            if (Pixel_Exist(image_temp, (int) xp, (int) yp))
            {
                color = SDL_GetPixel32(image_temp, (int) xp, (int) yp);
                SDL_PutPixel32(data->sdl.image, x, y, color);
            }
            else
            {
                SDL_PutPixel32(data->sdl.image,x,y,4294967295);
            }
        }
    }

    SDL_UnlockSurface(image_temp);
    SDL_FreeSurface(image_temp);
}
