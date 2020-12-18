#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

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

int max(int a, int b)
{
    if (a >= b)
        return a;
    return b;
}

int min(int a, int b)
{
    if (a <= b)
        return a;
    return b;
}


void save_result(char* path, char* str)
{
    FILE *file;
    file = fopen(path, "w");
    fprintf(file, "%s", str);
    fclose(file);
}









