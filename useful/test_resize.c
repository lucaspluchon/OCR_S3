#include <SDL2/SDL.h>
#include "../image_preprocessing/headers/preprocessing.h"
#include "builtin.h"

void test_sdl_neural(int* matrix)
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface* image = Image_Generate(32,32);

    for (int i = 0; i < 32; i++)
    {
        for (int j = 0; j < 32; j++)
        {
            if (matrix[i * 32 + j] == 1)
            {
                SDL_PutPixel32(image,i,j,Pixel_RGBto32(255,0,0,0));
            }
        }
    }

    SDL_Window* window = SDL_CreateWindow("SDL2 Displaying Image",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          image->w, image->h, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    PauseSDL();
}