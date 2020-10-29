#ifndef BUILTIN_H_INCLUDED
#define BUILTIN_H_INCLUDED

#include <stdbool.h>
#include "../type/pixel.h"

void DisplayError(char* message);
void Console_ReadString(char *var, char* message, int size);
bool FileExist(char* path);
void PauseSDL();
void swap(int* a, int* b);
size_t partition (int arr[], size_t low, size_t high);
void quickSort(int arr[], size_t low, size_t high);
int CalculMedian(int arr[],size_t size);
size_t max_size(size_t a, size_t b);
PixelBlock* Init_CharBlock(array_size size);
size_t offset(size_t block, size_t line, size_t chr, array_size size);

#endif // BUILTIN_H_INCLUDED
