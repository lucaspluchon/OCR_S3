#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "character_detection/char_detect.h"
#include "useful/builtin.h"
#include "image_system/image_system.h"
#include "image_system/image_manipulation.h"

void ImageDemo()
{
    char path[99] = {0};
    char rlsa[2] = {0};
    array_size size = {0,0,0};
    //int size = 0;
    Console_ReadString(path,"\nImage path : ", 99);
    Console_ReadString(rlsa,"Show RLSA (y or n) : ", 2);

    //------------------------------------------------------------------------
    //---- SDL INIT
    //------------------------------------------------------------------------
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface* image = Image_Load(path);
    SDL_Window* window = SDL_CreateWindow("SDL2 Displaying Image",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          image->w, image->h, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);


    //------------------------------------------------------------------------
    //---- PREPARE TO CHAR DETECTION
    //------------------------------------------------------------------------
    ApplyCorrection(image);
    SDL_Surface* image_rlsa = Detect_RLSA_Block(image,7);
    if (strcmp(rlsa,"y"))
        Image_ToRenderer(image,renderer);
    else
        Image_ToRenderer(image_rlsa,renderer);

    //------------------------------------------------------------------------
    //---- BLOC DETECTION
    //------------------------------------------------------------------------
    Count_Block(image, image_rlsa, &size);

    PixelBlock* char_block = Init_CharBlock(size);

    if (strcmp(rlsa,"y"))
        Detect_Block(image,image_rlsa,renderer,true,char_block,size);

    SDL_RenderPresent(renderer);
    free(char_block);
    SDL_FreeSurface(image);
    SDL_FreeSurface(image_rlsa);
    SDL_DestroyRenderer(renderer);
    PauseSDL();
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_Quit();
}
