#include<stdlib.h>
#include<stdio.h>
#include <SDL2/SDL.h>
#include "../type/pixel.h"
#include"../image_preprocessing/headers/preprocessing.h"
#include"../character_detection/headers/segmentation.h"
#include "read.h"
#include "NeuralNetworkTools.h"
#include"ForwardProp.h"
#include"BackProp.h"
#include<string.h>

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
        //int randPolice = (int)((randd() + 1 ) * 7 / 2);
        int randPolice = 0;

        char* filename = fileNames[(i - LowerBound) * 7 + randPolice];

        SDL_Surface* image = Image_Load(filename);

        struct text* text = apply_segmentation_for_training(filename);

        pixel_block caractere = text->blocks[0].lines[0].chrs[0];

        int* chr_image = get_pixel_block(image, caractere.left_top.x, caractere.left_top.y,
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
            char dirNum[25];
            sprintf(dirNum, "%i", (int)(i + lowerBound));


            char fileNum[25];
            sprintf(fileNum, "%i", (int)j);

            fileNames[i * 7 + j][13] = dirNum[0];
            fileNames[i * 7 + j][14] = dirNum[1];
            fileNames[i * 7 + j][16] = fileNum[0];
        }
    }


    NeuralNetwork* network = GenerateNetwork(Neural_Network_Entry_Size * Neural_Network_Entry_Size,
        hidenNumber, upperBound - lowerBound + 1);


    for (size_t i = 0; i < itteration; i++)
    {
        learn(network, (int)(lowerBound), (int)(upperBound), v, fileNames);
    }
    return network;
}

int testOnLetter(NeuralNetwork* network, int letter, size_t lowerBound)
{
    char filename[] = "data/letters/**/*.bmp";

    char dirNum[25];
    sprintf(dirNum, "%i", letter);

    //int randPolice = (int)((randd() + 1 ) * 7 / 2);
    int randPolice = 0;
    char fileNum[25];
    sprintf(fileNum, "%i", randPolice);

    filename[13] = dirNum[0];
    filename[14] = dirNum[1];
    filename[16] = fileNum[0];



    SDL_Surface* image = Image_Load(filename);

    struct text* text = apply_segmentation_for_training(filename);

    pixel_block caractere = text->blocks[0].lines[0].chrs[0];

    int* chr_image = get_pixel_block(image, caractere.left_top.x, caractere.left_top.y,
        caractere.right_bottom.x, caractere.right_bottom.y);

    int* chr_resized = resize(chr_image, caractere.right_bottom.x - caractere.left_top.x,
        caractere.right_bottom.y - caractere.left_top.y);

    for (size_t i = 0; i < network->inputNumber; i++)
    {
        network->activations->data[i] = chr_resized[i];
    }

    forwardProp(network);

    double *output = &(network->activations->data[network->inputNumber + network->hidenNumber]);
    size_t maxI = 0;
    for (size_t i = 0; i < network->outputNumber; i++)
    {
        if (output[i] > output[maxI])
        {
            maxI = i;
        }
        
    }
    int found = letter == (int)(lowerBound) + maxI;

    printf("%c - The network was given a %c and gessed it was a %c", letter, letter, (char)((int)(lowerBound) + maxI));
    if (found)
    {
        printf("            (gessed right)");
    }
    
    printf("\nthe outputs were :");
    printList(output, network->outputNumber);
    printf("\n\n");


    return found;

}

void testAllLetter(NeuralNetwork* network, size_t lowerBound, size_t upperBound)
{
    printf("testOnAllLetter :\n\n");

    int founds = 0;

    for (size_t i = lowerBound; i < upperBound; i++)
    {
        founds += testOnLetter(network, i, lowerBound);
    }
    
    printf("\nHe gessed %i / %i right... Not bad !", founds, (int)(upperBound - lowerBound + 1));
}



int main(int argc, char **argv[])
{
    if (argc != 6)
    {
        printf("Usage : \nmain double v  size_t itteration  size_t hidenNumber  size_t lowerBound  size_t upperBound");
        return 1;
    }
    double v = argv[1];
    size_t itteration = argv[2];
    size_t hidenNumber = argv[3];
    size_t testLen = argv[4];
    size_t lowerBound = argv[5];




    size_t upperBound = lowerBound + testLen;

    NeuralNetwork * trainedNetwork = fullTrain(v, itteration, hidenNumber, lowerBound, upperBound);

    testAllLetter(trainedNetwork, lowerBound, upperBound);

    //printNetwork(trainedNetwork);

    return 0;
}

