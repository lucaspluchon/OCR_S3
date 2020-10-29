#include <stdio.h>
#include <string.h>
#include "demo.h"
#include "useful/builtin.h"
#include "NeuralNetworks/DemoNeuralNetwork.h"

int main()
{
    char choice[50];
    printf("####OCR First presentation demo####\n");
    printf("0 - Image manipulation demo\n");
    printf("1 - XOR Neural Network demo without file reading\n");
    printf("2 - XOR Neural Network demo with file reading\n\n");
    Console_ReadString(choice, "Choose your mode: ", 99);

    if (!strcmp(choice,"0"))
    {
        ImageDemo();
    }
    
    if (!strcmp(choice,"1"))
    {
        DemoNeural();
    }
    
    if (!strcmp(choice,"2"))
    {
        demoWithLoad();
    }

	return 0;


}


