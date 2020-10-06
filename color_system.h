#ifndef COLOR_SYSTEM_H_INCLUDED
#define COLOR_SYSTEM_H_INCLUDED

Uint32 ColorToUInt(int a, int r, int g, int b);

uint8_t getR(Uint32 c);
uint8_t getG(Uint32 c);
uint8_t getB(Uint32 c);

int absRGB(double c);

Uint32 GrayScale_Pixel(Uint32 color);
Uint32 Contrast_Pixel(Uint32 color, int delta);
Uint32 Threshold_Pixel(Uint32 color, int n);
void Convolution_Pixel(SDL_Surface* image,int matrix[3][3], int x, int y,double factor);

#endif // COLOR_SYSTEM_H_INCLUDED
