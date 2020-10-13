#include "../include_ocr.h"


//Get RGB colors from an Uint32 color
uint8_t getR(Uint32 c)
{
    return c >> 16;
}

uint8_t getG(Uint32 c)
{
    return c >> 8;
}

uint8_t getB(Uint32 c)
{
    return c;
}

//Return UInt32 color from RGBA color
Uint32 ColorToUInt(int a, int r, int g, int b)
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
int absRGB(double c)
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

Uint32 GrayScale_Pixel(Uint32 color)
{
    int r = (int) getR(color);
    int g = (int) getG(color);
    int b = (int) getB(color);
    int gray = (r + g + b) / 3;
    return ColorToUInt(255,gray,gray,gray);
}

Uint32 Contrast_Pixel(Uint32 color, int delta)
{
    int r = (int) getR(color);
    int g = (int) getG(color);
    int b = (int) getB(color);
    double factor = (259 * (delta + 255))/(255 * (259 - delta));
    r = absRGB(factor * (r - 128) + 128);
    g = absRGB(factor * (g - 128) + 128);
    b = absRGB(factor * (b - 128) + 128);
    return ColorToUInt(255,r,g,b);
}

//Need to be apply on a gray scale color
Uint32 Threshold_Pixel(Uint32 color, int n)
{
    int r = (int) getR(color);
    if (r > n)
        return ColorToUInt(255,255,255,255);
    else
        return ColorToUInt(255,0,0,0);
}

void Convolution_Pixel(SDL_Surface* image,int matrix[3][3], int x, int y, double factor)
{
    Uint32 color = 0;
    double r = 0;
    double g = 0;
    double b = 0;

    if (x - 1 >= 0 && y - 1 >= 0)
    {
        color = SDL_GetPixel32(image,x-1,y-1);
        r += getR(color) * matrix[0][0]* factor;
        g += getG(color) * matrix[0][0]* factor;
        b += getB(color) * matrix[0][0]* factor;
    }
    if (y - 1 >= 0)
    {
        color = SDL_GetPixel32(image,x,y-1);
        r += getR(color) * matrix[1][0]* factor;
        g += getG(color) * matrix[1][0]* factor;
        b += getB(color) * matrix[1][0]* factor;
    }
    if (x + 1 < image->w && y - 1 >= 0)
    {
        color = SDL_GetPixel32(image,x+1,y-1);
        r += getR(color) * matrix[2][0]* factor;
        g += getG(color) * matrix[2][0]* factor;
        b += getB(color) * matrix[2][0]* factor;
    }

    if (x - 1 >= 0)
    {
        color = SDL_GetPixel32(image,x-1,y);
        r += getR(color) * matrix[0][1]* factor;
        g += getG(color) * matrix[0][1]* factor;
        b += getB(color) * matrix[0][1]* factor;
    }

    color = SDL_GetPixel32(image,x,y);
    r += getR(color) * matrix[1][1]* factor;
    g += getG(color) * matrix[1][1]* factor;
    b += getB(color) * matrix[1][1]* factor;

    if (x + 1 < image->w)
    {
        color = SDL_GetPixel32(image,x+1,y);
        r += getR(color) * matrix[2][1]* factor;
        g += getG(color) * matrix[2][1]* factor;
        b += getB(color) * matrix[2][1]* factor;
    }

    if (x - 1 >= 0 && y + 1 < image->h)
    {
        color = SDL_GetPixel32(image,x-1,y+1);
        r += getR(color) * matrix[0][2]* factor;
        g += getG(color) * matrix[0][2]* factor;
        b += getB(color) * matrix[0][2]* factor;
    }
    if (y + 1 < image->h)
    {
        color = SDL_GetPixel32(image,x,y+1);
        r += getR(color) * matrix[1][2]* factor;
        g += getG(color) * matrix[1][2]* factor;
        b += getB(color) * matrix[1][2]* factor;
    }
    if (x + 1 < image->w && y + 1 < image->h)
    {
        color = SDL_GetPixel32(image,x+1,y+1);
        r += getR(color) * matrix[2][2]* factor;
        g += getG(color) * matrix[2][2]* factor;
        b += getB(color) * matrix[2][2]* factor;
    }

    SDL_PutPixel32(image,x,y,ColorToUInt(255,absRGB(r),absRGB(g),absRGB(b)));
}

