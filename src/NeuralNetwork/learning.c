#include<stdlib.h>
#include<stdio.h>
#include<err.h>
#include <SDL2/SDL.h>
#include "../type/pixel.h"
#include"../image_preprocessing/headers/preprocessing.h"
#include"../character_detection/headers/segmentation.h"
#include "headers/read.h"
#include "headers/NeuralNetworkTools.h"
#include "headers/ForwardProp.h"
#include "headers/BackProp.h"
#include <string.h>


double* findDelta(NeuralNetwork* network, double v, int* inputs, double* expected,
     double *biasDeltaHiden, double *biasDeltaOut, double *deltaHiden, double *deltaOut)
{
    for (size_t i = 0; i < network->inputNumber; i++)
    {
        network->activations->data[i] = inputs[i];
    }

    forwardProp(network);


    double* outError = calloc(network->outputNumber, sizeof(double));
    if(outError == NULL)
        errx(1, "Memory allocation failed find delta 1");
    outputError(network, expected, outError);

    double* hidError = calloc(network->hidenNumber, sizeof(double));
    if(hidError == NULL)
        errx(1, "Memory allocation failed find delta 2");
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


void learn(NeuralNetwork* network, double v, int** allResized)
{
    double* biasDeltaHiden = calloc(network->hidenNumber, sizeof(double));
    double* biasDeltaOut = calloc(network->outputNumber, sizeof(double));
    double* deltaOut = calloc(network->outputNumber * network->hidenNumber, sizeof(double));
    double* deltaHiden = calloc(network->hidenNumber * network->inputNumber, sizeof(double));

    double * expected = calloc((network->outputNumber), sizeof(double));
    if(biasDeltaHiden == NULL || biasDeltaOut == NULL || deltaOut == NULL || deltaHiden == NULL || expected == NULL)
        errx(1, "Memory allocation failed learn");

    for (int i = 0; i < network->outputNumber; i++)
    {

        int randPolice = (int)((randd() + 1 ) * Number_Police / 2);

        int* chr_resized = allResized[i * Number_Police + randPolice];

        for (size_t k = 0; k < network->outputNumber; k++)
        {
            expected[k] = 0;
        }
        expected[i] = 1;

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

    free(expected);
}

int ** loadAllResized(char** fileNames, size_t outputNumber)
{
    int** allResized = malloc(sizeof(int*) * outputNumber * Number_Police);
    if (allResized == NULL)
        errx(1, "Memory allocation failed load all resized 1");
    for (size_t i = 0; i < outputNumber * Number_Police; i++)
    {
        allResized[i] = malloc(sizeof(int) * Neural_Network_Entry_Size * Neural_Network_Entry_Size);
        if (allResized[i] == NULL)
            errx(1, "Memory allocation failed load all resized 2");
    }

    for (int i = 0; i < outputNumber; i++)
    {
        for (int j = 0; j < Number_Police; j++)
        {
            char* filename = fileNames[i * Number_Police + j];

            ocr_data data = apply_segmentation_for_training(filename);
            struct text* text = data.text_array;
            SDL_Surface* image = data.sdl.image;


            pixel_block caractere = text->blocks[0].lines[0].chrs[0];

            int* chr_image = get_pixel_block(image, caractere.left_top.x, caractere.left_top.y,
                caractere.right_bottom.x, caractere.right_bottom.y);

            allResized[i * Number_Police + j] = resize(chr_image, caractere.right_bottom.x - caractere.left_top.x,
                caractere.right_bottom.y - caractere.left_top.y);
            free(chr_image);
        }
    }

    return allResized;
}


void fullTrain(NeuralNetwork * network, double v, size_t itteration)
{
    char** fileNames = malloc(network->outputNumber * Number_Police * sizeof(char*));
    if (fileNames == NULL)
        errx(1, "Memory allocation failed full train 1");

    char filenameBase[] = "data/letters/000/00.png";

    for (int i = 0; i < network->outputNumber; i++)
    {
        for (int j = 0; j < Number_Police; j++)
        {
            fileNames[i * Number_Police + j] = malloc(24 * sizeof(char));
            if (fileNames[i * Number_Police + j] == NULL)
                errx(1, "Memory allocation failed full train");
            for (size_t k = 0; k < 24; k++)
            {
                fileNames[i * Number_Police + j][k] = filenameBase[k];
            }
            char dirNum[25];
            sprintf(dirNum, "%i", (int)(network->asciiOutputs->data[i]));


            char fileNum[25];
            sprintf(fileNum, "%i", (int)j);

            if (network->asciiOutputs->data[i] < 100)
            {
                fileNames[i * Number_Police + j][14] = dirNum[0];
                fileNames[i * Number_Police + j][15] = dirNum[1];
            }
            else
            {
                fileNames[i * Number_Police + j][13] = dirNum[0];
                fileNames[i * Number_Police + j][14] = dirNum[1];
                fileNames[i * Number_Police + j][15] = dirNum[2];
            }

            if (j < 10)
            { 
                fileNames[i * Number_Police + j][18] = fileNum[0];
            }
            else
            {
                fileNames[i * Number_Police + j][17] = fileNum[0];
                fileNames[i * Number_Police + j][18] = fileNum[1];
            }
            
        }
    }

    int** allResized = loadAllResized(fileNames, network->outputNumber);

    for (size_t i = 0; i < itteration; i++)
    {
        learn(network, v, allResized);
    }
    for(size_t k; k < network->outputNumber * Number_Police; k++)
    {
        free(fileNames[k]);
        free(allResized[k]);
    }
    free(fileNames);
    free(allResized);

}


