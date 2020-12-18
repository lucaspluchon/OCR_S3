#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#include "headers/NeuralNetworkTools.h"
#include "headers/learning.h"
#include "headers/FileManagment.h"
#include "headers/read.h"
#include "headers/LearningTest.h"
#include "../character_detection/headers/segmentation.h"

void trainSaveTest()
{
    double v = 0.02;
    size_t itteration = 2000;
    size_t gen = 3;
    size_t hidenNumber = 52;
    size_t testLen = 26;
    size_t lowerBound = 65;
    size_t upperBound = 200;

    size_t lenOut = 0;
    double* asciiOutputs = malloc((upperBound - lowerBound + 1) * sizeof(double));

    for (size_t i = lowerBound; i <= upperBound; i++)
    {

        if (i >= (size_t)('0') && i <= (size_t)('9') ||
             i >= (size_t)('A') && i <= (size_t)('Z') ||
             i >= (size_t)('a') && i <= (size_t)('z'))
        {
            asciiOutputs[lenOut] = (double)i;
            lenOut++;
        }
        
    }

    


    NeuralNetwork* trainedNetwork = GenerateNetwork(Neural_Network_Entry_Size * Neural_Network_Entry_Size,
                                                    hidenNumber, lenOut, asciiOutputs);
    printf("Starting learning...\n");
    for(size_t i = 0; i < gen; i++)
    {
        time_t start;
        time_t end;
        time(&start);
        fullTrain(trainedNetwork, v, itteration);
        if (writeNetwork(trainedNetwork) == 1)
            printf("FAIL\n");
        time(&end);
        printf("Leanred %li / %li, (%.2f %%)------(in %ld sec   %ld sec remaining)\n", (i + 1) * itteration,
               gen * itteration, ((double)(i) + 1) * 100 / (double)(gen), end - start, (gen - i - 1) * (end - start));
    }

    printf("Learning done\n");
    testAllLetter(trainedNetwork);
    freeNetwork(trainedNetwork);

    free(asciiOutputs);

}

void reloadTest()
{
    NeuralNetwork * trainedNetwork = readNetwork();
    if (trainedNetwork == NULL)
        printf("No Network Saved");

    char* filename = "../image/article.bmp";
    ocr_data data = apply_segmentation_for_training(filename);
    fullRead(&data);
    freeNetwork(trainedNetwork);
}