#ifndef IMAGE_MANIPULATION_H_INCLUDED
#define IMAGE_MANIPULATION_H_INCLUDED

void Image_GrayScale(SDL_Surface* image);
void Image_Threshold(SDL_Surface* image, int threshold);
void Image_Median(SDL_Surface* image);
void Image_Convolution(SDL_Surface* image, int matrix[3][3], double factor);

void ApplyCorrection(SDL_Surface* image);


#endif // IMAGE_MANIPULATION_H_INCLUDED
