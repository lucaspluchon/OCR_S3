#ifndef OCR_S3_PREPROCESSING_H
#define OCR_S3_PREPROCESSING_H

#include <SDL2/SDL.h>
#include <stdbool.h>


void Image_Threshold(SDL_Surface* image, int threshold);

void Image_Convolution(SDL_Surface* image, int matrix[3][3], double factor);

void Image_GrayScale(SDL_Surface* image);

void Image_Median(SDL_Surface* image);
void Image_ToRenderer(SDL_Surface * image, SDL_Renderer* renderer);

SDL_Surface* Image_Copy(SDL_Surface* image);
SDL_Surface* Image_Load(char* path);

void SDL_PutPixel32(SDL_Surface *surface, int x, int y, Uint32 pixel);
Uint32 SDL_GetPixel32(SDL_Surface *surface, int x, int y);
uint8_t Pixel_GetR(Uint32 c);
uint8_t Pixel_GetG(Uint32 c);
uint8_t Pixel_GetB(Uint32 c);
Uint32 Pixel_RGBto32(int a, int r, int g, int b);
int Pixel_absRGB(double c);
bool Pixel_Exist(SDL_Surface* image, int x, int y);
void SDL_DrawLine(SDL_Surface *image, int x0, int y0, int x1, int y1, Uint32 color);

void Image_Rotate(SDL_Surface* image, double angle);

void Image_ApplyCorrection(SDL_Surface* image, int threshold, double angle);

#endif
