#include <stdio.h>
#include <string.h>
#include "demo.h"
#include "useful/builtin.h"

int main()
{
    char choice[50];
    printf("####OCR First presentation demo####\n");
    printf("0 - Image manipulation demo\n");
    printf("1 - XOR Neural Network demo\n\n");
    Console_ReadString(choice, "Choose your mode: ", 99);

    if (!strcmp(choice,"0"))
    {
        ImageDemo();
    }

	return 0;


}


