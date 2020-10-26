/*#include "../include_ocr.h"
#include "character_detection.h"

//#####COUNT PART
void Count_BlocVertical(SDL_Surface* image, int* nbBlock, int* nbLine, int* nbChar)
{
    bool detected_black = false;
    bool started_detect_block = false;
    int r = 0;
    bool inDetection = false;
    Uint32 c = 0;
    int start_x = 0;
    int end_x = 0;

    for (int x = 0; x < image->w; x++)
    {
        detected_black = false;
        for (int y = 0; y < image->h; y++)
        {
            c = SDL_GetPixel32(image,x,y);
            r = Pixel_GetR(c);
            detected_black = detected_black || (r == 0);
        }

        started_detect_block = detected_black == true;

        if (started_detect_block == true)
        {
            if (inDetection == false)
            {
                start_x = x;
            }
            inDetection = true;
        }

        if (started_detect_block == false && inDetection)
        {
            inDetection = false;
            end_x = x;
            *nbBlock += 1;
            Count_Line(image,start_x,end_x,nbLine,nbChar);
        }
    }
}

void Count_Line(SDL_Surface* image, int x_start, int x_end, int* nbLine, int* nbChar)
{
    bool detected_black = false;
    bool started_detect_line = false;
    int r = 0;
    bool inDectection = 0;
    Uint32 c = 0;
    int start_y = 0;
    int end_y = 0;

    for (int y = 0; y < image->h; y++)
    {
        detected_black = false;

        for (int x = x_start; x <= x_end; x++)
        {
            c = SDL_GetPixel32(image,x,y);
            r = Pixel_GetR(c);
            detected_black = detected_black || (r == 0);
        }

        started_detect_line = detected_black == true;

        if (started_detect_line == true)
        {
            if (inDectection == false)
            {
                start_y = y;
            }
            inDectection = true;
        }

        if (started_detect_line == false && inDectection)
        {
            inDectection = false;
            end_y = y;
            *nbLine += 1;
            Count_Char(image,start_y,end_y,nbChar);
        }
    }
}

void Count_Char(SDL_Surface* image, int y_start, int y_end, int* nbChar)
{
    bool detected_black = false;
    bool started_detect_char = false;
    int r = 0;
    bool inDetection = false;
    Uint32 c = 0;
    for (int x = 0; x < image->w; x++)
    {
        detected_black = false;

        for (int y = y_start; y <= y_end; y++)
        {
            c = SDL_GetPixel32(image,x,y);
            r = Pixel_GetR(c);
            detected_black = detected_black || (r == 0);
        }

        started_detect_char = detected_black == true;

        if (started_detect_char == true)
        {
            inDetection = true;
        }

        if (started_detect_char == false && inDetection)
        {
            inDetection = false;
            *nbChar +=1;
        }
    }
}

//#####DETECTION PART

int Dectect_AverageVertical(SDL_Surface* image)
{
    bool detected_black = false;
    bool started_detect_block = false;
    bool startCount = false;
    int r = 0;
    bool inDetection = false;
    Uint32 c = 0;
    int nbSpace = 0;
    int totalBlockSpace = 0;

    for (int x = 0; x < image->w; x++)
    {
        detected_black = false;
        for (int y = 0; y < image->h; y++)
        {
            c = SDL_GetPixel32(image,x,y);
            r = Pixel_GetR(c);
            detected_black = detected_black || (r == 0);
        }

        started_detect_block = detected_black == true;

        if (started_detect_block == true)
        {
            if (inDetection == false)
            {
                startCount = false;
            }
            inDetection = true;
        }

        if (started_detect_block == false && inDetection)
        {
            inDetection = false;
            startCount = true;
            nbSpace++;
        }

        if (startCount)
            totalBlockSpace++;
    }
    return totalBlockSpace / nbSpace;
}

void Dectect_BlocVertical(SDL_Surface* image, SDL_Renderer* renderer, bool DrawLine)
{
    bool detected_black = false;
    bool started_detect_block = false;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    int r = 0;
    bool inDetection = false;
    Uint32 c = 0;
    int start_x = 0;
    int end_x = 0;

    for (int x = 0; x < image->w; x++)
    {
        detected_black = false;
        for (int y = 0; y < image->h; y++)
        {
            c = SDL_GetPixel32(image,x,y);
            r = Pixel_GetR(c);
            detected_black = detected_black || (r == 0);
        }

        started_detect_block = detected_black == true;

        if (started_detect_block == true)
        {
            if (inDetection == false)
            {
                start_x = x;
                if (DrawLine)
                    SDL_RenderDrawLine(renderer, x, 0, x, image->h - 1);
            }
            inDetection = true;
        }

        if (started_detect_block == false && inDetection)
        {
            inDetection = false;
            if (DrawLine)
                SDL_RenderDrawLine(renderer, x, 0, x, image->h - 1);
            end_x = x;
            Dectect_Line(image,renderer,start_x,end_x,DrawLine);
        }
    }
}

void Dectect_Line(SDL_Surface* image, SDL_Renderer* renderer, int x_start, int x_end, bool DrawLine)
{
    bool detected_black = false;
    bool started_detect_line = false;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    int r = 0;
    bool inDectection = 0;
    Uint32 c = 0;

    int start_y = 0;
    int end_y = 0;

    for (int y = 0; y < image->h; y++)
    {
        detected_black = false;

        for (int x = x_start; x <= x_end; x++)
        {
            c = SDL_GetPixel32(image,x,y);
            r = Pixel_GetR(c);
            detected_black = detected_black || (r == 0);
        }

        started_detect_line = detected_black == true;

        if (started_detect_line == true)
        {
            if (inDectection == false)
            {
                if (DrawLine)
                    SDL_RenderDrawLine(renderer, x_start, y, x_end, y);
                start_y = y;
            }
            inDectection = true;
        }

        if (started_detect_line == false && inDectection)
        {
            inDectection = false;
            end_y = y;
            if (DrawLine)
                SDL_RenderDrawLine(renderer, x_start, y, x_end, y);
            Dectect_Char(image,renderer,start_y,end_y,DrawLine);
        }
    }
}

void Dectect_Char(SDL_Surface* image, SDL_Renderer* renderer, int y_start, int y_end, bool DrawLine)
{
    bool detected_black = false;
    bool started_detect_char = false;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    int r = 0;
    bool inDetection = false;
    Uint32 c = 0;

    for (int x = 0; x < image->w; x++)
    {
        detected_black = false;

        for (int y = y_start; y <= y_end; y++)
        {
            c = SDL_GetPixel32(image,x,y);
            r = Pixel_GetR(c);
            detected_black = detected_black || (r == 0);
        }

        started_detect_char = detected_black == true;

        if (started_detect_char == true)
        {
            if (inDetection == false)
                if (DrawLine)
                    SDL_RenderDrawLine(renderer, x, y_start, x, y_end);
            inDetection = true;
        }

        if (started_detect_char == false && inDetection)
        {
            inDetection = false;
            if (DrawLine)
                SDL_RenderDrawLine(renderer, x, y_start, x, y_end);
        }
    }
}*/
