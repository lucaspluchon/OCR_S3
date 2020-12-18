#ifndef OCR_S3_PREPROCESSING_H
#define OCR_S3_PREPROCESSING_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "../../type/data.h"


void Image_Threshold(ocr_data* data, int threshold);

void Image_Convolution(ocr_data* data, int matrix[3][3], double factor);

void Image_GrayScale(ocr_data* data);

void Image_Median(ocr_data* data);
void Image_ToRenderer(SDL_Surface * image, SDL_Renderer* renderer);

SDL_Surface* Image_Copy(SDL_Surface* image);
SDL_Surface* Image_Load(char* path);
SDL_Surface* Image_Generate(int w, int h);

void SDL_PutPixel32(SDL_Surface *surface, int x, int y, Uint32 pixel);
Uint32 SDL_GetPixel32(SDL_Surface *surface, int x, int y);
uint8_t Pixel_GetR(Uint32 c);
uint8_t Pixel_GetG(Uint32 c);
uint8_t Pixel_GetB(Uint32 c);
Uint32 Pixel_RGBto32(int a, int r, int g, int b);
int Pixel_absRGB(double c);
bool Pixel_Exist(SDL_Surface* image, int x, int y);
void SDL_DrawLine(SDL_Surface *image, int x0, int y0, int x1, int y1, Uint32 color);

void Image_Rotate(ocr_data* data, double angle);

void Image_ApplyCorrection(ocr_data* data);

void Image_AutoLock(SDL_Surface* image);


#endif
