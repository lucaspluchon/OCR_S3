#include<stdlib.h>
#include<stdio.h>
#include<err.h>
#include <SDL2/SDL.h>
#include "../type/pixel.h"
#include"../image_preprocessing/headers/preprocessing.h"
#include"../character_detection/headers/segmentation.h"
#include "NeuralNetwork/headers/read.h"
#include "NeuralNetwork/headers/NeuralNetworkTools.h"
#include"NeuralNetwork/headers/ForwardProp.h"
#include"NeuralNetwork/headers/BackProp.h"
#include<string.h>
#include "NeuralNetwork/headers/FileManagment.h"
#include "../useful/test_resize.h"




int ** loadAllResized(char** fileNames, size_t lowerBound, size_t upperBound);

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
        errx(1, "Memory allocation failed");
    outputError(network, expected, outError);

    double* hidError = calloc(network->hidenNumber, sizeof(double));
    if(hidError == NULL)
        errx(1, "Memory allocation failed");
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
        errx(1, "Memory allocation failed");

    for (int i = 0; i < network->outputNumber; i++)
    {

        int randPolice = (int)((randd() + 1 ) * 7 / 2);

        int* chr_resized = allResized[i * 7 + randPolice];

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



void fullTrain(NeuralNetwork * network, double v, size_t itteration, size_t hidenNumber, size_t lowerBound, size_t upperBound)
{


    char** fileNames = malloc((upperBound - lowerBound + 1) * 7 * sizeof(char*));
    if (fileNames == NULL)
        errx(1, "Memory allocation failed");

    char filenameBase[] = "data/letters/**/*.bmp";

    for (int i = 0; i < (upperBound - lowerBound + 1); i++)
    {
        for (int j = 0; j < 7; j++)
        {
            fileNames[i * 7 + j] = malloc(22 * sizeof(char));
            if (fileNames[i * 7 + j] == NULL)
                errx(1, "Memory allocation failed");
            for (size_t k = 0; k < 22; k++)
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




    int** allResized = loadAllResized(fileNames, lowerBound, upperBound);

    for (size_t i = 0; i < itteration; i++)
    {
        learn(network, v, allResized);
    }
    for(size_t k; k < (upperBound - lowerBound + 1) * 7; k++)
    {
        free(fileNames[k]);
        free(allResized[k]);
    }
    free(fileNames);
    free(allResized);

}


int ** loadAllResized(char** fileNames, size_t lowerBound, size_t upperBound)
{

    int** allResized = malloc(sizeof(int*) * (upperBound - lowerBound + 1) * 7);
    if (allResized == NULL)
        errx(1, "Memory allocation failed");
    for (size_t i = 0; i < (upperBound - lowerBound + 1) * 7; i++)
    {
        allResized[i] = malloc(sizeof(int) * Neural_Network_Entry_Size * Neural_Network_Entry_Size);
        if (allResized[i] == NULL)
            errx(1, "Memory allocation failed");
    }

    for (int i = 0; i < (upperBound - lowerBound + 1); i++)
    {
        for (int j = 0; j < 7; j++)
        {
            char* filename = fileNames[i * 7 + j];
//            filename[21] = '\0';

            ocr_data data = apply_segmentation_for_training(filename);
            struct text* text = data.text_array;
            SDL_Surface* image = data.sdl.image;



            pixel_block caractere = text->blocks[0].lines[0].chrs[0];

            int* chr_image = get_pixel_block(image, caractere.left_top.x, caractere.left_top.y,
                caractere.right_bottom.x, caractere.right_bottom.y);

            allResized[i * 7 + j] = resize(chr_image, caractere.right_bottom.x - caractere.left_top.x,
                caractere.right_bottom.y - caractere.left_top.y);
            free(chr_image);
        }
    }

    return allResized;
}






