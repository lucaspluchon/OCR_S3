#ifndef OCR_S3_SEGMENTATION_H
#define OCR_S3_SEGMENTATION_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "../image_preprocessing/headers/preprocessing.h"
#include "../type/pixel.h"
#include "../useful/builtin.h"

SDL_Surface* Detect_RLSA_Block(SDL_Surface* image, int n);

void Count_Block(SDL_Surface* image, SDL_Surface* image_copy, array_size* size);
void Count_VerticalBlock(SDL_Surface* image, SDL_Surface* image_copy,
                         PixelBlock block, bool detected_whitebefore,
                         array_size* size);
void Count_HorizontalBlock(SDL_Surface* image, SDL_Surface* image_copy,
                           PixelBlock block, bool detected_whitebefore,
                           array_size* size);
void Detect_Block(SDL_Surface* image, SDL_Surface* image_rlsa,
                  SDL_Renderer* renderer, bool DrawLine, PixelBlock char_block[],
                  array_size size);
void Detect_VerticalBlock(SDL_Surface* image, SDL_Surface* image_rlsa,
                          SDL_Renderer* renderer, bool DrawLine,
                          PixelBlock block, bool detected_whitebefore,
                          PixelBlock char_block[], array_size size,
                          array_size pos);
void Detect_HorizontalBlock(SDL_Surface* image, SDL_Surface* image_rlsa,
                            SDL_Renderer* renderer, bool DrawLine,
                            PixelBlock block, bool detected_whitebefore,
                            PixelBlock char_block[], array_size size,
                            array_size pos);

void Count_Line(SDL_Surface* image, PixelBlock block, array_size* size);
void Detect_Line(SDL_Surface* image, SDL_Renderer* renderer, bool DrawLine,
                 PixelBlock block, PixelBlock char_block[], array_size size,
                 array_size pos);

void Count_Char(SDL_Surface* image, PixelBlock block, array_size* size);
void Detect_Char(SDL_Surface* image, SDL_Renderer* renderer, bool DrawLine,
                 PixelBlock block, PixelBlock char_block[], array_size size,
                 array_size pos);


#endif //OCR_S3_SEGMENTATION_H
