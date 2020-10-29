#ifndef CHAR_DETECT_H_INCLUDED
#define CHAR_DETECT_H_INCLUDED

#ifdef _WIN32
#	include <SDL.h>
#else
#	include <SDL2/SDL.h>
#endif
#include <stdbool.h>
#include "../type/pixel.h"


SDL_Surface* Detect_RLSA_Block(SDL_Surface* image, int n);

void Count_Block(SDL_Surface* image, SDL_Surface* image_copy, array_size* size);

void Count_VerticalBlock(SDL_Surface* image, SDL_Surface* image_copy,
                         PixelBlock block, bool detected_whitebefore,
                         array_size* size);

void Count_HorizontalBlock(SDL_Surface* image, SDL_Surface* image_copy,
                           PixelBlock block, bool detected_whitebefore,
                           array_size* size);

void Count_Line(SDL_Surface* image, PixelBlock block, array_size* size);
void Count_Char(SDL_Surface* image, PixelBlock block, array_size* size);

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

void Detect_Line(SDL_Surface* image, SDL_Renderer* renderer, bool DrawLine,
                  PixelBlock block, PixelBlock char_block[], array_size size,
                  array_size pos);

void Detect_Char(SDL_Surface* image, SDL_Renderer* renderer, bool DrawLine,
                  PixelBlock block, PixelBlock char_block[], array_size size,
                  array_size pos);


#endif // CHAR_DETECT_H_INCLUDED
