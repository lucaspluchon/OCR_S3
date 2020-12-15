#include<stdlib.h>
#include<stdio.h>
#include <SDL2/SDL.h>
#include "../type/pixel.h"
#include "reading/read.h"
#include "NeuralNetworkTools.h"
#include"ForwardProp.h"
#include"BackProp.h"

#define Neural_Network_Entry_Size 32

double* findDelta(NeuralNetwork* network, double v, int* inputs, double* expected,
     double *biasDeltaHiden, double *biasDeltaOut, double *deltaHiden, double *deltaOut)
{
    for (size_t i = 0; i < network->inputNumber; i++)
    {
        network->activations->data[i] = inputs[i];
    }

    forwardProp(network);



    double* outError = calloc(network->outputNumber, sizeof(double));
    outputError(network, expected, outError);

    double* hidError = calloc(network->hidenNumber, sizeof(double));
    hidenErrors(network, outError, hidError);
    // printf("Hiden error\n");
    // printf("%f, %f\n", hidError[0], hidError[1]);

    
    biasDelta(network->hidenNumber, hidError, v, biasDeltaHiden);
    biasDelta(network->outputNumber, outError, v, biasDeltaOut);

    // printf("Delta bias ; \n");
    // printf("%f ; %f ; %f\n", bDelta[0], bDelta[1], bDelta[2]);

    outputWeightDelta(network, outError, v, deltaOut);

    // printf("Delta out ; \n");
    // printf("%f ; %f\n", dOut[0], dOut[1]);
    
    hidenWeightDelta(network, hidError, v, deltaHiden);

    // printf("Delta hid ; \n");
    // printf("%f ; %f ; %f ; %f\n", dHid[0], dHid[1], dHid[2], dHid[3]);
    free(outError);
    free(hidError);

     
}


void learn(NeuralNetwork* network, int LowerBound, int UpperBound, double v, char** fileNames)
{
    double* biasDeltaHiden = calloc(network->hidenNumber, sizeof(double));
    double* biasDeltaOut = calloc(network->outputNumber, sizeof(double));
    double* deltaOut = calloc(network->outputNumber * network->hidenNumber, sizeof(double));
    double* deltaHiden = calloc(network->hidenNumber * network->inputNumber, sizeof(double));



    for (int i = LowerBound; i <= UpperBound; i++)
    {  
        int randPolice = (int)((randd() + 1 ) * 7 / 2);

        char* filename = fileNames[(i - LowerBound) * 7 + randPolice];

        SDL_Surface* image = Image_Load(filename);

        struct text* text = apply_segmentation_for_training(filename);

        pixel_block caractere = text->blocks[0].lines[0].chrs[0];

        int** chr_image = get_pixel_block(image, caractere.left_top.x, caractere.left_top.y,
            caractere.right_bottom.x, caractere.right_bottom.y);

        int* chr_resized = resize(chr_image, caractere.right_bottom.x - caractere.left_top.x,
            caractere.right_bottom.y - caractere.left_top.y);

        double * expected = calloc((UpperBound - LowerBound + 1), sizeof(double));

        expected[i-LowerBound] = 1;

        findDelta(network, v, chr_resized, expected, biasDeltaHiden, biasDeltaOut, deltaHiden, deltaOut);
        
    }


    // application of deltas
    for (size_t i = 0; i < network->hidenNumber; i++)
    {
        network->bias->data[i] += biasDeltaHiden[i];
    }

    for (size_t i = 0; i < network->outputNumber; i++)
    {
        network->bias->data[i + network->hidenNumber] += biasDeltaOut[i];
    }

    for (size_t i = 0; i < network->hidenNumber * network->inputNumber; i++)
    {
        network->inputWeights->data[i] += deltaHiden[i];
    }

    for (size_t i = 0; i < network->hidenNumber * network->outputNumber; i++)
    {
        network->hidenWeights->data[i] += deltaOut[i];
    }

    // freeing
    free(biasDeltaHiden);
    free(biasDeltaOut);
    free(deltaHiden);
    free(deltaOut);
}



NeuralNetwork* fullTrain(double v, size_t itteration, size_t hidenNumber, size_t lowerBound, size_t upperBound)
{
    double v = 1;
    size_t itteration = 1;

    size_t hidenNumber = 69;


    size_t lowerBound = 65;
    size_t upperBound = 90;


    char** fileNames = malloc((upperBound - lowerBound + 1) * 7 * sizeof(char*));

    char filenameBase[] = "data/letters/**/*.bmp";

    for (int i = 0; i < (upperBound - lowerBound + 1); i++)
    {
        for (int j = 0; j < 7; j++)
        {
        fileNames[i * 7 + j] = malloc(21 * sizeof(char));
        for (size_t k = 0; k < 21; k++)
        {
            fileNames[i * 7 + j][k] = filenameBase[k];
        }
        char dirNum[2];
        itoa(i + lowerBound, dirNum, 10);


        char fileNum[1];
        itoa(j, fileNum, 10);

        fileNames[i * 7 + j][13] = dirNum[0];
        fileNames[i * 7 + j][14] = dirNum[1];
        fileNames[i * 7 + j][16] = fileNum[0];
    }


    NeuralNetwork* network = GenerateNetwork(Neural_Network_Entry_Size * Neural_Network_Entry_Size,
        hidenNumber, upperBound - lowerBound + 1);

    for (size_t i = 0; i < itteration; i++)
    {
        learn(network, (int)(lowerBound), (int)(upperBound), v, fileNames);
    }
    
}

int main()
{
    NeuralNetwork * trainedNetwork = fullTrain(1, 1, 69, 65, 90);
    printNetwork(trainNetwork);

    return 0;
}

