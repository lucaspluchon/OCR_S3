#include <SDL2/SDL.h>
#include "data.h"
#include "pixel.h"

void Data_delete(ocr_data* data)
{
    if (data != NULL)
    {
        if (data->text_array != NULL)
            textArray_delete(data->text_array);
        if (data->sdl.image != NULL)
            SDL_FreeSurface(data->sdl.image);
        if (data->sdl.image_segmented != NULL)
            SDL_FreeSurface(data->sdl.image_segmented);
        if (data->sdl.image_rlsa != NULL)
            SDL_FreeSurface(data->sdl.image_rlsa);
        if (data->sdl.image_original != NULL)
            SDL_FreeSurface(data->sdl.image_original);
        if (data->ui.image_pixbuf != NULL)
            g_object_unref(data->ui.image_pixbuf);
        if (strcmp(data->file_path,"") != 0)
            g_free(data->file_path);
    }
}
