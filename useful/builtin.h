#ifndef BUILTIN_H_INCLUDED
#define BUILTIN_H_INCLUDED

void DisplayError(char* message);
void Console_ReadString(char *var, char* message, int size);
bool FileExist(char* path);
void PauseSDL();
void swap(int* a, int* b);
int partition (int arr[], int low, int high);
void quickSort(int arr[], int low, int high);
int CalculMedian(int arr[],int size);

#endif // BUILTIN_H_INCLUDED
