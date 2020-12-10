#include "headers/segmentation.h"

void Count_Line(SDL_Surface* image, PixelBlock block, array_size* size)
{
    bool detected_black = false;
    bool inDetection = false;
    size_t nbLine_temp = 0;
    int c = 0;
    PixelBlock block_temp = block;

    for (int y = block.left_top.y; y <= block.left_bottom.y; y++)
    {
        detected_black = false;
        for (int x = block.left_top.x; x <= block.right_top.x; x++)
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
                block_temp.left_top.y = y;
                block_temp.right_top.y = y;
            }
            inDetection = true;
        }

        if ((detected_black == false || y == image->h - 1) && inDetection)
        {
            inDetection = false;
            block_temp.left_bottom.y = y;
            block_temp.right_bottom.y = y;
            nbLine_temp++;
            Count_Char(image,block_temp,size);
        }
    }

    size->nb_line = max_size(size->nb_line,nbLine_temp);
}


void Detect_Line(SDL_Surface* image, SDL_Renderer* renderer, bool DrawLine,
                 PixelBlock block, PixelBlock char_block[], array_size size,
                 array_size pos)
{
    bool detected_black = false;
    bool inDetection = false;
    int c = 0;
    PixelBlock block_temp = block;

    for (int y = block.left_top.y; y <= block.left_bottom.y; y++)
    {
        detected_black = false;
        for (int x = block.left_top.x; x <= block.right_top.x; x++)
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
                block_temp.left_top.y = y;
                block_temp.right_top.y = y;
                if (DrawLine)
                {
                    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                    SDL_RenderDrawLine(renderer, block_temp.left_top.x,
                                       block_temp.left_top.y,
                                       block_temp.right_top.x,
                                       block_temp.right_top.y);
                }
            }
            inDetection = true;
        }

        if ((detected_black == false || y == image->h - 1) && inDetection)
        {
            inDetection = false;
            block_temp.left_bottom.y = y;
            block_temp.right_bottom.y = y;
            if (DrawLine)
            {
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                SDL_RenderDrawLine(renderer, block_temp.left_bottom.x,
                                   block_temp.left_bottom.y,
                                   block_temp.right_bottom.x,
                                   block_temp.right_bottom.y);
            }
            Detect_Char(image,renderer,DrawLine,block_temp,char_block,size,pos);
            pos.nb_line++;
        }
    }

}