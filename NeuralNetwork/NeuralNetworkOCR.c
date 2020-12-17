#include "NeuralNetwork/headers/NeuralNetworkTools.h"
#include<stdlib.h>
#include<stdio.h>
#include"NeuralNetwork/headers/ForwardProp.h"
#include"NeuralNetwork/headers/BackProp.h"
#include"NeuralNetwork/headers/FileManagment.h"
#include "NeuralNetwork/headers/LearningTest.h"

int main(int argc, char** argv)
{

    /*
    if (argc != 6)
    {
        printf("Usage : \nmain double v  size_t itteration  size_t hidenNumber  size_t lowerBound  size_t upperBound");
        return 1;
    }

    double v = (double)(strtol(argv[1], NULL, 10));
    size_t itteration = (size_t)(strtol(argv[2], NULL, 10));
    size_t hidenNumber = (size_t)(strtol(argv[3], NULL, 10));
    size_t testLen = (size_t)(strtol(argv[4], NULL, 10));
    size_t lowerBound = (size_t)(strtol(argv[5], NULL, 10));
    */
    trainSaveTest();
    //reloadTest();
    //struct NeuralNetwork* network = readNetwork();
    //printNetwork(network);
    //testAllLetter(network);

    return 0;
}

