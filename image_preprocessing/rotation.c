#include "headers/preprocessing.h"
#include "../type/data.h"
#include "../type/pixel.h"
#include "../useful/builtin.h"

int Pixel_Rotate_X(int x, int y, int center_x, int center_y, double cos_angle, double sin_angle)
{
    double res = (x - center_x) * cos_angle - (y - center_y) * sin_angle + center_x;
    return (int) res;
}

int Pixel_Rotate_Y(int x, int y, int center_x, int center_y, double cos_angle, double sin_angle)
{
    double res = (x - center_x) * sin_angle + (y - center_y) * cos_angle + center_y;
    return (int) res;
}

void Image_Rotate(ocr_data* data, double angle)
{
    Uint32 color;
    int xp;
    int yp;
    angle = angle * M_PI / 180;
    double cos_angle = cos(angle);
    double sin_angle = sin(angle);
    int center_x = (int) data->sdl.image->w / 2;
    int center_y = (int) data->sdl.image->h / 2;
    pixel Image_Corner[4] = {{0,0},{data->sdl.image->w,0},{0,data->sdl.image->h},{data->sdl.image->w,data->sdl.image->h}};
    int max_x = 0;
    int max_y = 0;
    int min_x = data->sdl.image->w;
    int min_y = data->sdl.image->h;
    int res_x;
    int res_y;

    for (int i = 0; i < 4; i++)
    {
        res_x = Pixel_Rotate_X(Image_Corner[i].x,Image_Corner[i].y,center_x,center_y,cos_angle,sin_angle);
        res_y = Pixel_Rotate_Y(Image_Corner[i].x,Image_Corner[i].y,center_x,center_y,cos_angle,sin_angle);

        max_x = max(max_x,res_x);
        max_y = max(max_y,res_y);
        min_x = min(min_x,res_x);
        min_y = min(min_y,res_y);
    }

    SDL_Surface* image_temp = Image_Copy(data->sdl.image);
    SDL_LockSurface(image_temp);

    free(data->sdl.image);
    data->sdl.image = Image_Generate(max_x + abs(min_x) , max_y + abs(min_y));

    for (int x = 0; x < image_temp->w; x++)
    {
        for (int y = 0; y < image_temp->h; y++)
        {
            xp = Pixel_Rotate_X(x,y,center_x,center_y,cos_angle,sin_angle) + abs(min_x);
            yp = Pixel_Rotate_Y(x,y,center_x,center_y,cos_angle,sin_angle) + abs(min_y);
            if (Pixel_Exist(data->sdl.image, xp, yp))
            {
                color = SDL_GetPixel32(image_temp, x, y);
                SDL_PutPixel32(data->sdl.image, xp, yp, color);
            }
        }
    }

    SDL_UnlockSurface(image_temp);
    SDL_FreeSurface(image_temp);
}

