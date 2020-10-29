#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#	include <io.h>
#else
#	include <unistd.h>
#endif
#include <string.h>
#include "../character_detection/char_detect.h"

void PauseSDL()
{
    int continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_Quit();
}

void DisplayError(char* message)
{
    printf("%s",message);
    exit(1);
}

bool FileExist(char* path)
{
    if(access(path, 0 ))
    {
        printf("'%s' doesn't exist !", path);
        return false;
    }
    return true;
}

void Console_ReadString(char *var, char* message, int size)
{
    printf("%s",message);
    char *start = NULL;

    if (fgets(var, size, stdin) != NULL)
    {
        start = strchr(var, '\n');
        if (start != NULL)
        {
            *start = '\0';
        }
    }
}

//Useful function for QuickSort
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

//Useful function for Quicksort
size_t partition (int arr[], size_t low, size_t high)
{
    int pivot = arr[high];
    size_t i = (low - 1);

    for (size_t j = low; j <= high- 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], size_t low, size_t high)
{

    if (low < high)
    {
        size_t pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

size_t CalculMedian(int arr[],size_t size)
{
    quickSort(arr, 0, size-1);
    size_t i = size / 2;
    if (size % 2 == 0)
    {
        return (arr[i] + arr[i + 1]) / 2;
    }
    return arr[i+1];
}

size_t max_size(size_t a, size_t b)
{
    if (a >= b)
        return a;
    return b;
}

PixelBlock* Init_CharBlock(array_size size)
{
    size_t size_array = size.nb_block * size.nb_char * size.nb_line;
    PixelBlock* a = malloc(size_array*sizeof(PixelBlock));

    for (size_t i = 0; i < size_array; i++)
    {
        PixelBlock block = {{-1,-1},{-1,-1},{-1,-1},{-1,-1}};
        a[i] = block;
    }

    return a;
}

size_t offset(size_t block, size_t line, size_t chr, array_size size)
{
    return (chr * size.nb_block * size.nb_line) + (line * size.nb_block) + block;
}
