#include "include_ocr.h"


int main(int argc, char *argv[])
{
    char choice[50];
    printf("####OCR First presentation demo####\n");
    printf("0 - Image manipulation demo\n");
    printf("1 - XOR Neural Network demo\n\n");
    Console_ReadString(choice, "Choose your mode: ", 99);

    if (!strcmp(choice,"0"))
    {
        char path[99] = {0};
        Console_ReadString(path,"\nImage path : ", 99);

        SDL_Init(SDL_INIT_VIDEO);

        SDL_Surface* image = Image_Load(path);

        SDL_Window* window = SDL_CreateWindow("SDL2 Displaying Image", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, image->w, image->h, 0);

        ApplyCorrection(image);

        Image_Show(image ,window);

        PauseSDL();

    }

	return 0;


}


