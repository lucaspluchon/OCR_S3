#include "headers/preprocessing.h"
Uint32 SDL_GetPixel32(SDL_Surface *surface, int x, int y)
{
    Uint8 *p = (Uint8*)surface->pixels + y * surface->pitch + x * 4;
    return *(Uint32*)p;
}

void SDL_PutPixel32(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    Uint8 *p = (Uint8*)surface->pixels + y * surface->pitch + x * 4;
    *(Uint32*)p = pixel;
}

void SDL_DrawLine(SDL_Surface *image, int x0, int y0, int x1, int y1, Uint32 color)
{
    double x = x1 - x0;
    double y = y1 - y0;
    double length = sqrt( x*x + y*y );
    double add_x = x / length;
    double add_y = y / length;
    x = x0;
    y = y0;

    for (int i = 0; i < length; i += 1)
    {
        SDL_PutPixel32(image, x, y, color);
        x += add_x;
        y += add_y;
    }
}

uint8_t Pixel_GetR(Uint32 c)
{
    return  c >> 16;
}

uint8_t Pixel_GetG(Uint32 c)
{
    return c >> 8;
}

uint8_t Pixel_GetB(Uint32 c)
{
    return c;
}

//Return UInt32 color from RGBA color
Uint32 Pixel_RGBto32(int a, int r, int g, int b)
{
    Uint32 c;
    c = a;
    c <<= 8;
    c |= r;
    c <<= 8;
    c |= g;
    c <<= 8;
    c |= b;
    return c;
}

//Clamp the RGB at 255 and 0
int Pixel_absRGB(double c)
{
    if (c > 255)
    {
        return 255;
    }

    if (c < 0)
    {
        return 0;
    }

    return (int) c;
}

bool Pixel_Exist(SDL_Surface* image, int x, int y)
{
    if (x < 0 || x >= image->w || y < 0 || y >= image->h)
        return false;
    return true;
}
