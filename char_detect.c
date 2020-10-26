#include "include_ocr.h"
#include "image_system/image_system.h"
#include "image_system/color_system.h"
#include "char_detect.h"

SDL_Surface* DetectBlock(SDL_Surface* image, int n)
{
    SDL_Surface* image_temp = Image_Copy(image);
    SDL_LockSurface(image);
    SDL_LockSurface(image_temp);

    int c = 0;
    int c2 = 0;
    int breaking = false;

    for (int x = 0; x < image->w; x++)
    {
        for (int y = 0; y < image->h; y++)
        {
            c = Pixel_GetR(SDL_GetPixel32(image,x,y));
            if (c == 255)
            {
                for (int x2 = x-n; x2 <= x + n; x2++)
                {
                    for (int y2 = y-n; y2 <= y + n; y2++)
                    if (Pixel_Exist(image,x2,y2))
                    {
                        c2 = Pixel_GetR(SDL_GetPixel32(image,x2,y2));
                        if (c2 == 0)
                        {
                            SDL_PutPixel32(image_temp,x,y,Pixel_RGBto32(255,0,0,0));
                            breaking = true;
                            break;
                        }
                    }
                    if (breaking)
                    {
                        breaking = false;
                        break;
                    }
                }
            }
        }
    }
    SDL_UnlockSurface(image);
    SDL_UnlockSurface(image_temp);
    return image_temp;
}

//Counting functions

void Count_VerticalBlock(SDL_Surface* image, SDL_Surface* image_copy, PixelBlock block, bool detected_whitebefore, int* nbBlock, int* nbLine, int* nbChar)
{
    bool detected_black = false;
    int c = 0;
    bool inDetection = false;
    bool detected_white = false;
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
                Count_HorizontalBlock(image, image_copy, block_temp, detected_white, nbBlock, nbLine, nbChar);
            else
            {
                Count_Line(image,block_temp, nbLine, nbChar);
                *nbBlock += 1;
            }
        }
    }
}

void Count_HorizontalBlock(SDL_Surface* image, SDL_Surface* image_copy, PixelBlock block, bool detected_whitebefore, int* nbBlock, int* nbLine, int* nbChar)
{
    bool detected_black = false;
    int c = 0;
    bool inDetection = false;
    bool detected_white = false;
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
                Count_VerticalBlock(image, image_copy, block_temp, detected_white, nbBlock, nbLine, nbChar);
            else
            {
                Count_Line(image,block_temp, nbLine, nbChar);
                *nbBlock += 1;
            }

        }
    }
}

void Count_Line(SDL_Surface* image, PixelBlock block, int* nbLine, int* nbChar)
{
    bool detected_black = false;
    int c = 0;
    bool inDetection = false;
    PixelBlock block_temp = block;
    int nbLine_temp = 0;

    for (int y = block.left_top.y; y <= block.left_bottom.y; y++)
    {
        detected_black = false;
        for (int x = block.left_top.x; x <= block.right_top.x; x++)
        {
            c = Pixel_GetR(SDL_GetPixel32(image,x,y));
            detected_black = detected_black || (c == 0);
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
            Count_Char(image,block_temp,nbChar);
        }
    }

    *nbLine = max_int(*nbLine,nbLine_temp);
}

void Count_Char(SDL_Surface* image, PixelBlock block, int* nbChar)
{
    bool detected_black = false;
    int c = 0;
    bool inDetection = false;
    int nbChar_temp = 0;

    for (int x = block.left_top.x; x <= block.right_top.x; x++)
    {
        detected_black = false;
        for (int y = block.left_top.y; y <= block.left_bottom.y; y++)
        {
            c = Pixel_GetR(SDL_GetPixel32(image,x,y));
            detected_black = detected_black || (c == 0);
        }

        if (detected_black)
            inDetection = true;

        if ((detected_black == false || x == image->w - 1) && inDetection)
        {
            inDetection = false;
            nbChar_temp++;
        }
    }
    *nbChar = max_int(*nbChar,nbChar_temp);
}

//Put all the char in a list
void Dectect_VerticalBlock(SDL_Surface* image, SDL_Surface* image_copy, SDL_Renderer* renderer, bool DrawLine, PixelBlock block, bool detected_whitebefore)
{
    bool detected_black = false;
    int c = 0;
    bool inDetection = false;
    bool detected_white = false;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
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
                if (DrawLine)
                {
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                    SDL_RenderDrawLine(renderer, block_temp.left_top.x, block_temp.left_top.y, block_temp.left_bottom.x, block_temp.left_bottom.y);
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
                SDL_RenderDrawLine(renderer, block_temp.right_top.x, block_temp.right_top.y, block_temp.right_bottom.x, block_temp.right_bottom.y);
            }
            if (detected_white == true || detected_whitebefore == true)
                Dectect_HorizontalBlock(image, image_copy, renderer, DrawLine, block_temp, detected_white);
            else
                Dectect_Line(image,renderer,DrawLine,block_temp);
        }
    }
}

void Dectect_HorizontalBlock(SDL_Surface* image, SDL_Surface* image_copy, SDL_Renderer* renderer, bool DrawLine, PixelBlock block, bool detected_whitebefore)
{
    bool detected_black = false;
    int c = 0;
    bool inDetection = false;
    bool detected_white = false;
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
                if (DrawLine)
                {
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                    SDL_RenderDrawLine(renderer, block_temp.left_top.x, block_temp.left_top.y, block_temp.right_top.x, block_temp.right_top.y);
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
                SDL_RenderDrawLine(renderer, block_temp.left_bottom.x, block_temp.left_bottom.y, block_temp.right_bottom.x, block_temp.right_bottom.y);
            }
            if (detected_white == true || detected_whitebefore == true)
                Dectect_VerticalBlock(image, image_copy, renderer, DrawLine, block_temp, detected_white);
            else
                Dectect_Line(image,renderer,DrawLine,block_temp);

        }
    }
}

void Dectect_Line(SDL_Surface* image, SDL_Renderer* renderer, bool DrawLine, PixelBlock block)
{
    bool detected_black = false;
    int c = 0;
    bool inDetection = false;
    PixelBlock block_temp = block;

    for (int y = block.left_top.y; y <= block.left_bottom.y; y++)
    {
        detected_black = false;
        for (int x = block.left_top.x; x <= block.right_top.x; x++)
        {
            c = Pixel_GetR(SDL_GetPixel32(image,x,y));
            detected_black = detected_black || (c == 0);
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
                    SDL_RenderDrawLine(renderer, block_temp.left_top.x, block_temp.left_top.y, block_temp.right_top.x, block_temp.right_top.y);
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
                SDL_RenderDrawLine(renderer, block_temp.left_bottom.x, block_temp.left_bottom.y, block_temp.right_bottom.x, block_temp.right_bottom.y);
            }
            Dectect_Char(image,renderer,DrawLine,block_temp);
        }
    }

}

void Dectect_Char(SDL_Surface* image, SDL_Renderer* renderer, bool DrawLine, PixelBlock block)
{
    bool detected_black = false;
    int c = 0;
    bool inDetection = false;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    PixelBlock block_temp = block;

    for (int x = block.left_top.x; x <= block.right_top.x; x++)
    {
        detected_black = false;
        for (int y = block.left_top.y; y <= block.left_bottom.y; y++)
        {
            c = Pixel_GetR(SDL_GetPixel32(image,x,y));
            detected_black = detected_black || (c == 0);
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
                    SDL_RenderDrawLine(renderer, block_temp.left_top.x, block_temp.left_top.y, block_temp.left_bottom.x, block_temp.left_bottom.y);
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
                SDL_RenderDrawLine(renderer, block_temp.right_top.x, block_temp.right_top.y, block_temp.right_bottom.x, block_temp.right_bottom.y);
            }
        }
    }
}


