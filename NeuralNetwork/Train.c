#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#include "NeuralNetwork/headers/NeuralNetworkTools.h"
#include "NeuralNetwork/headers/learning.h"
#include "NeuralNetwork/headers/FileManagment.h"
#include "NeuralNetwork/headers/read.h"
#include "NeuralNetwork/headers/LearningTest.h"

void trainSaveTest()
{
    double v = 0.05;
    size_t itteration = 10000;
    size_t gen = 15;
    size_t hidenNumber = 55;
    size_t testLen = 26;
    size_t lowerBound = 65;
    size_t upperBound = 200;

    size_t lenOut = 0;
    double* asciiOutputs = malloc((upperBound - lowerBound + 1) * sizeof(double));

    for (size_t i = lowerBound; i <= upperBound; i++)
    {

        if (i >= (size_t)('0') && i <= (size_t)('9') ||
             i >= (size_t)('A') && i <= (size_t)('Z') ||
             i >= (size_t)('a') && i <= (size_t)('z') && i != 105 && i != 106)
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

    char* filename = "../image/testim.jpg";
    fullRead(trainedNetwork, filename);
    freeNetwork(trainedNetwork);
}