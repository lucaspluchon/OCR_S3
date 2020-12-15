#ifndef READ_H
#define READ_H

int** get_pixel_block(SDL_Surface* image, int x1, int y1, int x2, int y2);
int* resize(int** chr, int widthChr, int heightChr);
void parcours(SDL_Surface* image, text* arr);
#endif
