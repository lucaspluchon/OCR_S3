#include "include_ocr.h"
#include "char_detect.h"

void ImageDemo()
{
    char path[99] = {0};
    int nbBlock = 0;
    int nbLine = 0;
    int nbChar = 0;
    Console_ReadString(path,"\nImage path : ", 99);

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Surface* image = Image_Load(path);

    SDL_Window* window = SDL_CreateWindow("SDL2 Displaying Image", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, image->w, image->h, 0);

    ApplyCorrection(image);
    SDL_Surface* image_block = DetectBlock(image,7);

    //Generate Renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    Image_ToRenderer(image,window,renderer);

    PixelBlock block = {{0,0},{image->w-1,0},{0,image->h-1},{image->w-1,image->h-1}};
    Count_VerticalBlock(image,image_block,block,true,&nbBlock,&nbLine,&nbChar);

    //int size = nbBlock * nbLine * nbChar;
    //PixelBlock char_block[size];
    //Init_ArrayPixel(char_block,size);

    Dectect_VerticalBlock(image,image_block,renderer,true,block,true);



    SDL_RenderPresent(renderer);

    PauseSDL();
}
