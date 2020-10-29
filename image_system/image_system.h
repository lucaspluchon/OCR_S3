#ifndef IMAGE_SYSTEM_H_INCLUDED
#define IMAGE_SYSTEM_H_INCLUDED

void Image_ToRenderer(SDL_Surface * image, SDL_Renderer* renderer);
SDL_Surface* Image_Load(char* path);
SDL_Surface* Image_Copy(SDL_Surface* image);

void SDL_PutPixel32(SDL_Surface *surface, int x, int y, Uint32 pixel);
Uint32 SDL_GetPixel32(SDL_Surface *surface, int x, int y);

#endif // IMAGE_SYSTEM_H_INCLUDED
