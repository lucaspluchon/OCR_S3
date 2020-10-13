#ifndef IMAGE_SYSTEM_H_INCLUDED
#define IMAGE_SYSTEM_H_INCLUDED

void ShowImage(SDL_Surface * image, SDL_Window* window);
SDL_Surface* LoadImage(char* path);
void SDL_PutPixel32(SDL_Surface *surface, int x, int y, Uint32 pixel);
void ApplyCorrection(SDL_Surface* image);
Uint32 SDL_GetPixel32(SDL_Surface *surface, int x, int y);

#endif // IMAGE_SYSTEM_H_INCLUDED
