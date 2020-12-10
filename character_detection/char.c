#include "headers/segmentation.h"


void Count_Char(SDL_Surface* image, PixelBlock block, array_size* size)
{
    bool detected_black = false;
    bool inDetection = false;
    size_t nbChar_temp = 0;
    int c = 0;

    for (int x = block.left_top.x; x <= block.right_top.x; x++)
    {
        detected_black = false;
        for (int y = block.left_top.y; y <= block.left_bottom.y; y++)
        {
            c = Pixel_GetR(SDL_GetPixel32(image,x,y));
            if (c == 0)
            {
                detected_black = true;
                break;
            }
        }

        if (detected_black)
            inDetection = true;

        if ((detected_black == false || x == image->w - 1) && inDetection)
        {
            inDetection = false;
            nbChar_temp++;
        }
    }
    size->nb_char = max_size(size->nb_char,nbChar_temp);
}

void Detect_Char(SDL_Surface* image, SDL_Renderer* renderer, bool DrawLine,
                 PixelBlock block, PixelBlock char_block[], array_size size,
                 array_size pos)
{
    bool detected_black = false;
    bool inDetection = false;
    int c = 0;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    PixelBlock block_temp = block;

    for (int x = block.left_top.x; x <= block.right_top.x; x++)
    {
        detected_black = false;
        for (int y = block.left_top.y; y <= block.left_bottom.y; y++)
        {
            c = Pixel_GetR(SDL_GetPixel32(image,x,y));
            if (c == 0)
            {
                detected_black = true;
                break;
            }
        }

        if (detected_black)
        {
            if (inDetection == false)
            {
                block_temp.left_top.x = x;
                block_temp.left_bottom.x = x;
                if (DrawLine)
                {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                    SDL_RenderDrawLine(renderer, block_temp.left_top.x,
                                       block_temp.left_top.y,
                                       block_temp.left_bottom.x,
                                       block_temp.left_bottom.y);
                }
            }
            inDetection = true;
        }

        if ((detected_black == false || x == image->w - 1) && inDetection)
        {
            inDetection = false;
            block_temp.right_top.x = x;
            block_temp.right_bottom.x = x;
            if (DrawLine)
            {
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                SDL_RenderDrawLine(renderer, block_temp.right_top.x,
                                   block_temp.right_top.y,
                                   block_temp.right_bottom.x,
                                   block_temp.right_bottom.y);
            }
            char_block[offset(pos.nb_block,pos.nb_line,pos.nb_char,size)] = block_temp;
            pos.nb_char++;
        }
    }
}

