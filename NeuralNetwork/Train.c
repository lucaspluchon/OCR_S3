#include<stdlib.h>
#include<stdio.h>

#include "NeuralNetwork/headers/NeuralNetworkTools.h"
#include "NeuralNetwork/headers/learning.h"
#include "NeuralNetwork/headers/FileManagment.h"
#include "NeuralNetwork/headers/read.h"


void trainSaveTest()
{
    double v = 0.05;
    size_t itteration = 1000;
    size_t gen = 50;
    size_t hidenNumber = 35;
    size_t testLen = 26;
    size_t lowerBound = 65;

    size_t upperBound = lowerBound + testLen - 1;

    NeuralNetwork* trainedNetwork = GenerateNetwork(Neural_Network_Entry_Size * Neural_Network_Entry_Size,
                                                    hidenNumber, upperBound - lowerBound + 1, lowerBound);
    printf("Starting learning...\n");
    for(size_t i = 0; i < gen; i++)
    {
        fullTrain(trainedNetwork, v, itteration, hidenNumber, lowerBound, upperBound);
        if (writeNetwork(trainedNetwork) == 1)
            printf("FAIL\n");
        printf("Leanred %li / %li, (%.2f %%)\n", (i + 1) * itteration, gen * itteration, ((double)(i) + 1) * 100 / (double)(gen));
    }

    printf("Learning done\n");
    testAllLetter(trainedNetwork, lowerBound, upperBound);
    freeNetwork(trainedNetwork);

}

void reloadTest()
{
    NeuralNetwork * trainedNetwork = readNetwork();
    if (trainedNetwork == NULL)
        printf("No Network Saved");

    char* filename = "../image/test42.png";
    fullRead(trainedNetwork, filename);
    freeNetwork(trainedNetwork);
}