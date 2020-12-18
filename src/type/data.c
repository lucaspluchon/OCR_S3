#include <SDL2/SDL.h>
#include "data.h"
#include "pixel.h"
#include "err.h"
#include "../NeuralNetwork/headers/NeuralNetworkTools.h"

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
    }
}

ocr_string* string_new()
{
    ocr_string* res = malloc(sizeof(ocr_string));
    res->size = 0;
    res->capacity = 1;
    res->string = malloc(sizeof(char));
    if (res->string == NULL)
        errx(1,"Not enough memory to add a new char!");

    return res;
}

void string_doubleCapacity(ocr_string* string_vector)
{
    string_vector->capacity *= 2;
    char* tmp = realloc(string_vector->string,sizeof (char) * string_vector->capacity);
    if (tmp == NULL)
        errx(1,"Not enough memory to add a new char!");
    else
        string_vector->string = tmp;
}

void string_append(ocr_string* string_vector, char c)
{
    string_vector->size++;
    if (string_vector->size >= string_vector->capacity)
        string_doubleCapacity(string_vector);
    string_vector->string[string_vector->size - 1] = c;
}

void string_free(ocr_string* string_vector)
{
    string_vector->size = 0;
    string_vector->capacity = 0;
    free(string_vector->string);
    string_vector->string = NULL;
    free(string_vector);
}