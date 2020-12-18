#include <SDL2/SDL.h>
#include "../image_preprocessing/headers/preprocessing.h"
#include "builtin.h"

/*
 * Test function for neural network
 */

void test_sdl_neural(int* matrix, int w, int h)
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface* image = Image_Generate(w,h);

    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            if (matrix[i * h + j])
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

    SDL_FreeSurface(image);
}