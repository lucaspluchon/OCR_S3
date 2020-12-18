#ifndef READ_H
#define READ_H

#include"NeuralNetworkTools.h"
#include "../../type/pixel.h"
#include "../../type/data.h"
#include <SDL2/SDL.h>

int* get_pixel_block(SDL_Surface* image, int x1, int y1, int x2, int y2);
int* resize(int* chr, int widthChr, int heightChr);
char readLetter(NeuralNetwork* network, pixel_block caractere, SDL_Surface* image);
void fullRead(ocr_data* data);
#endif
