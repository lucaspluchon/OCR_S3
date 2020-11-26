#ifndef COLOR_SYSTEM_H_INCLUDED
#define COLOR_SYSTEM_H_INCLUDED

#include <stdbool.h>

uint8_t Pixel_GetR(Uint32 c);
uint8_t Pixel_GetG(Uint32 c);
uint8_t Pixel_GetB(Uint32 c);

Uint32 Pixel_RGBto32(int a, int r, int g, int b);

int Pixel_absRGB(double c);

bool Pixel_Exist(SDL_Surface* image, int x, int y);
Uint32 Pixel_Grayscale(Uint32 color);
double Pixel_Deviation(SDL_Surface* image, int x, int y, int m);
int Pixel_DetectTreshold(SDL_Surface* image, int x, int y, double k);
Uint32 Pixel_Treshold(Uint32 color, int treshold);
Uint32 Pixel_Median(SDL_Surface* image, int x, int y);
Uint32 Pixel_Convolution(SDL_Surface* image,int matrix[3][3], int x, int y,double factor);

#endif // COLOR_SYSTEM_H_INCLUDED
