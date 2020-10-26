#ifndef CHAR_DETECT_H_INCLUDED
#define CHAR_DETECT_H_INCLUDED

typedef struct pixel pixel;
struct pixel
{
    int x;
    int y;
};

typedef struct PixelBlock PixelBlock;
struct PixelBlock
{
    pixel left_top;
    pixel right_top;
    pixel left_bottom;
    pixel right_bottom;
};

SDL_Surface* DetectBlock(SDL_Surface* image, int n);
void Count_VerticalBlock(SDL_Surface* image, SDL_Surface* image_copy, PixelBlock block, bool detected_whitebefore, int* nbBlock, int* nbLine, int* nbChar);
void Count_HorizontalBlock(SDL_Surface* image, SDL_Surface* image_copy, PixelBlock block, bool detected_whitebefore, int* nbBlock, int* nbLine, int* nbChar);
void Count_Line(SDL_Surface* image, PixelBlock block, int* nbLine, int* nbChar);
void Count_Char(SDL_Surface* image, PixelBlock block,int* nbChar);
void Dectect_VerticalBlock(SDL_Surface* image, SDL_Surface* image_copy, SDL_Renderer* renderer, bool DrawLine, PixelBlock block, bool detected_whitebefore);
void Dectect_HorizontalBlock(SDL_Surface* image, SDL_Surface* image_copy, SDL_Renderer* renderer, bool DrawLine, PixelBlock block, bool detected_whitebefore);
void Dectect_Line(SDL_Surface* image, SDL_Renderer* renderer, bool DrawLine, PixelBlock block);
void Dectect_Char(SDL_Surface* image, SDL_Renderer* renderer, bool DrawLine, PixelBlock block);


#endif // CHAR_DETECT_H_INCLUDED
