#include "include_ocr.h"


int main(int argc, char *argv[])
{
    char path[99] = {0};
    ConsoleReadString(path,"Image path : ", 99);

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Surface* image = Image_Load(path);

	SDL_Window* window = SDL_CreateWindow("SDL2 Displaying Image", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, image->w, image->h, 0);

	ApplyCorrection(image);

	Image_Show(image ,window);

	PauseSDL();

	return 0;


}


