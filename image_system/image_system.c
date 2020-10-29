#ifdef _WIN32
#	include <SDL.h>
#else
#	include <SDL2/SDL.h>
#endif
#include <stdlib.h>
#include "../useful/builtin.h"

//------------------------------------------------------------------------
//---- ALL THE NECESSARY FUNCTION TO MANIPULATE SDL SURFACE
//------------------------------------------------------------------------

void Image_ToRenderer(SDL_Surface * image, SDL_Renderer* renderer)
{
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
}

SDL_Surface* Image_Load(char* path)
{
    if (!FileExist(path))
    {
        exit(1);
    }

    return SDL_LoadBMP(path);
}

SDL_Surface* Image_Copy(SDL_Surface* image)
{
    return SDL_ConvertSurface(image, image->format, SDL_SWSURFACE);
}

//------------------------------------------------------------------------
//---- PUT A PIXEL ON A SDL SURFACE FROM AN HEXA COLOR
//------------------------------------------------------------------------
void SDL_PutPixel32(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    Uint8 *p = (Uint8*)surface->pixels + y * surface->pitch + x * 4;
    *(Uint32*)p = pixel;
}

//------------------------------------------------------------------------
//---- GIVE A HEXA COLOR FROM A SDL SURFACE
//------------------------------------------------------------------------
Uint32 SDL_GetPixel32(SDL_Surface *surface, int x, int y)
{
    Uint8 *p = (Uint8*)surface->pixels + y * surface->pitch + x * 4;
    return *(Uint32*)p;
}


