#include "../include_ocr.h"

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
}

void DisplayError(char* message)
{
    printf("%s",message);
    exit(1);
}

bool FileExist(char* path)
{
    if(access(path, F_OK ))
    {
        printf("'%s' doesn't exist !", path);
        return false;
    }
    return true;
}

void ConsoleReadString(char *var, char* message, int size)
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
int partition (int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high- 1; j++)
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

void quickSort(int arr[], int low, int high)
{

    if (low < high)
    {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int CalculMedian(int arr[],int size)
{
    quickSort(arr, 0, size-1);
    int i = size / 2;
    if (size % 2 == 0)
    {
        return (arr[i] + arr[i + 1]) / 2;
    }
    return arr[i+1];
}
