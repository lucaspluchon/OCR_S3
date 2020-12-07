#include "headers/segmentation.h"

void Count_Block(SDL_Surface* image, SDL_Surface* image_copy, array_size* size)
{
    PixelBlock block = {{0,0},{image->w-1,0},{0,image->h-1},
                        {image->w-1,image->h-1}};

    Count_VerticalBlock(image, image_copy, block, true, size);
}

void Count_VerticalBlock(SDL_Surface* image, SDL_Surface* image_copy,
                         PixelBlock block, bool detected_whitebefore,
                         array_size* size)
{
    bool detected_black = false;
    bool inDetection = false;
    bool detected_white = false;
    int c = 0;
    PixelBlock block_temp = block;

    for (int x = block.left_top.x; x <= block.right_top.x; x++)
    {
        detected_black = false;
        detected_white = false;
        for (int y = block.left_top.y; y <= block.left_bottom.y; y++)
        {
            c = Pixel_GetR(SDL_GetPixel32(image_copy,x,y));
            detected_black = detected_black || (c == 0);
            detected_white = detected_white && (c == 255);
        }

        if (detected_black)
        {
            if (inDetection == false)
            {
                block_temp.left_top.x = x;
                block_temp.left_bottom.x = x;
            }
            inDetection = true;
        }

        if ((detected_black == false || x == image->w - 1) && inDetection)
        {
            inDetection = false;
            block_temp.right_top.x = x;
            block_temp.right_bottom.x = x;
            if (detected_white == true || detected_whitebefore == true)
                Count_HorizontalBlock(image, image_copy, block_temp,
                                      detected_white, size);
            else
            {
                Count_Line(image,block_temp, size);
                size->nb_block += 1;
            }
        }
    }
}

void Count_HorizontalBlock(SDL_Surface* image, SDL_Surface* image_copy,
                           PixelBlock block, bool detected_whitebefore,
                           array_size* size)
{
    bool detected_black = false;
    bool inDetection = false;
    bool detected_white = false;
    int c = 0;
    PixelBlock block_temp = block;

    for (int y = block.left_top.y; y <= block.left_bottom.y; y++)
    {
        detected_black = false;
        detected_white = false;
        for (int x = block.left_top.x; x <= block.right_top.x; x++)
        {
            c = Pixel_GetR(SDL_GetPixel32(image_copy,x,y));
            detected_black = detected_black || (c == 0);
            detected_white = detected_white && (c == 255);
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
            if (detected_white == true || detected_whitebefore == true)
                Count_VerticalBlock(image, image_copy, block_temp,
                                    detected_white, size);
            else
            {
                Count_Line(image,block_temp, size);
                size->nb_block += 1;
            }

        }
    }
}

void Detect_Block(SDL_Surface* image, SDL_Surface* image_rlsa,
                  SDL_Renderer* renderer, bool DrawLine, PixelBlock char_block[],
                  array_size size)
{
    PixelBlock block = {{0,0},{image->w-1,0},{0,image->h-1},
                        {image->w-1,image->h-1}};

    array_size pos = {0,0,0};
    Detect_VerticalBlock(image, image_rlsa, renderer, DrawLine, block, true,
                         char_block, size, pos);

}

void Detect_VerticalBlock(SDL_Surface* image, SDL_Surface* image_rlsa,
                          SDL_Renderer* renderer, bool DrawLine,
                          PixelBlock block, bool detected_whitebefore,
                          PixelBlock char_block[], array_size size,
                          array_size pos)
{
    bool detected_black = false;
    bool detected_white = false;
    bool inDetection = false;
    int c = 0;
    PixelBlock block_temp = block;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    for (int x = block.left_top.x; x <= block.right_top.x; x++)
    {
        detected_black = false;
        detected_white = false;
        for (int y = block.left_top.y; y <= block.left_bottom.y; y++)
        {
            c = Pixel_GetR(SDL_GetPixel32(image_rlsa,x,y));
            detected_black = detected_black || (c == 0);
            detected_white = detected_white && (c == 255);
        }

        if (detected_black)
        {
            if (inDetection == false)
            {
                block_temp.left_top.x = x;
                block_temp.left_bottom.x = x;
                if (DrawLine)
                {
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
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
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_RenderDrawLine(renderer, block_temp.right_top.x,
                                   block_temp.right_top.y,
                                   block_temp.right_bottom.x,
                                   block_temp.right_bottom.y);
            }
            if (detected_white == true || detected_whitebefore == true)
                Detect_HorizontalBlock(image, image_rlsa, renderer, DrawLine,
                                       block_temp, detected_white,
                                       char_block, size, pos);
            else
            {
                Detect_Line(image,renderer,DrawLine,block_temp,
                            char_block, size, pos);
                pos.nb_block++;
            }
        }
    }
}

void Detect_HorizontalBlock(SDL_Surface* image, SDL_Surface* image_rlsa,
                            SDL_Renderer* renderer, bool DrawLine,
                            PixelBlock block, bool detected_whitebefore,
                            PixelBlock char_block[], array_size size,
                            array_size pos)
{
    bool detected_black = false;
    bool detected_white = false;
    bool inDetection = false;
    int c = 0;
    PixelBlock block_temp = block;

    for (int y = block.left_top.y; y <= block.left_bottom.y; y++)
    {
        detected_black = false;
        detected_white = false;
        for (int x = block.left_top.x; x <= block.right_top.x; x++)
        {
            c = Pixel_GetR(SDL_GetPixel32(image_rlsa,x,y));
            detected_black = detected_black || (c == 0);
            detected_white = detected_white && (c == 255);
        }

        if (detected_black)
        {
            if (inDetection == false)
            {
                block_temp.left_top.y = y;
                block_temp.right_top.y = y;
                if (DrawLine)
                {
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
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
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_RenderDrawLine(renderer, block_temp.left_bottom.x,
                                   block_temp.left_bottom.y,
                                   block_temp.right_bottom.x,
                                   block_temp.right_bottom.y);
            }
            if (detected_white == true || detected_whitebefore == true)
                Detect_VerticalBlock(image, image_rlsa, renderer, DrawLine,
                                     block_temp, detected_white,
                                     char_block, size, pos);
            else
            {
                Detect_Line(image,renderer,DrawLine,block_temp,
                            char_block, size, pos);
                pos.nb_block++;
            }

        }
    }
}