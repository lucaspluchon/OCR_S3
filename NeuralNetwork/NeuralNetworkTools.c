#include <math.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<err.h>
#include"NeuralNetworkTools.h"

double sigmoideDerivate(double x)
{
    return x * (1 - x);
}

double sigmoid(double x)
{
   return 1 / (1 + exp(-x));
}

double randd()
{
    return (((double)rand() / (RAND_MAX)) * 2) - 1;
}


NeuralNetwork* GenerateNetwork(size_t inputNumber, size_t hidenNumber, size_t outputNumber)
{
    NeuralNetwork* network = malloc(sizeof(NeuralNetwork));
    if (network == NULL)
        errx(1, "Memory allocation failed");
    network->inputNumber = inputNumber;
    network->hidenNumber = hidenNumber;
    network->outputNumber = outputNumber;

    network->activations = malloc(sizeof(ListSet));
    if (network->activations == NULL)
        errx(1, "Memory allocation failed");
    network->activations->size = inputNumber + hidenNumber + outputNumber;
    network->activations->data = calloc(inputNumber + hidenNumber + outputNumber, sizeof(double));
    if (network->activations->data == NULL)
        errx(1, "Memory allocation failed");

    network->bias = malloc(sizeof(ListSet));
    if (network->bias == NULL)
        errx(1, "Memory allocation failed");
    network->bias->size = hidenNumber + outputNumber;
    network->bias->data = malloc((hidenNumber + outputNumber) * sizeof(double));
    if (network->bias->data == NULL)
        errx(1, "Memory allocation failed");
    for(size_t i = 0; i < network->bias->size; i++)
    {
        network->bias->data[i] = randd();
    }

    network->inputWeights = malloc(sizeof(ListSet));
    if (network->inputWeights == NULL)
        errx(1, "Memory allocation failed");
    network->inputWeights->size = inputNumber * hidenNumber;
    network->inputWeights->data = malloc((inputNumber * hidenNumber) * sizeof(double));
    if (network->inputWeights->data == NULL)
        errx(1, "Memory allocation failed");
    for(size_t i = 0; i < network->inputWeights->size; i++)
    {
        network->inputWeights->data[i] = randd();
    }

    network->hidenWeights = malloc(sizeof(ListSet));
    if (network->hidenWeights == NULL)
        errx(1, "Memory allocation failed");
    network->hidenWeights->size = outputNumber * hidenNumber;
    network->hidenWeights->data = malloc((outputNumber * hidenNumber) * sizeof(double));
    if (network->hidenWeights->data == NULL)
        errx(1, "Memory allocation failed");
    for(size_t i = 0; i < network->hidenWeights->size; i++)
    {
        network->hidenWeights->data[i] = randd();
    }

    return network;

}

void freeNetwork(NeuralNetwork* network)
{
    free(network->activations->data);
    free(network->activations);

    free(network->bias->data);
    free(network->bias);

    free(network->inputWeights->data);
    free(network->inputWeights);

    free(network->hidenWeights->data);
    free(network->hidenWeights);

    free(network);

}

// void GenerateNetwork(Network* network, RowMark* rowMark, size_t inputsNumber, size_t outputsNumber, size_t hidenRowNumber, size_t* hidenRowLen)
// {

//     size_t size = 0;
//     for(size_t i = 0; i < hidenRowNumber; i++)
//     { 
//         size += hidenRowLen[i];
//     }
//     size += inputsNumber + outputsNumber;

//     //Size init
//     network->size = size;

//     //Row mark init
//     rowMark->len = hidenRowNumber + 3;

//     rowMark->lens = malloc(sizeof(double*) * (hidenRowNumber + 3));

//     //Data init
//     network->data = calloc(size, sizeof(double) * (size + outputsNumber + inputsNumber));

//     //Row mark valuation
//     size_t i = 1;
//     rowMark->lens[0] = network->data;
//     size_t sum = inputsNumber;
//     for(; i < hidenRowNumber + 1; i++)
//     {
//         rowMark->lens[i] = &(network->data[sum]);
//         sum += hidenRowLen[i - 1];
//     }
//     rowMark->lens[i] = &(network->data[sum]);
//     rowMark->lens[i + 1] = &(network->data[sum + outputsNumber]);
//     network->rowMark = rowMark;
// }


// void printList(double* list, double* end)
// {
//     printf("[");
//     for(double* p = list; p < end; p++)
//     {
//         printf(" %f ", *p);
//     }
//     printf("]\n");
// }

// void printNetwork(Network* network)
// {
//     printf("=========Network(size %zu)=========\n", network->size);
//     printf("Inputs :\n    ");
//     printList(network->rowMark->lens[0], network->rowMark->lens[1]);
//     printf("Hiden layers :\n");
//     for(size_t i = 1; i < network->rowMark->len - 2; i++)
//     {
//         printf("   ");
//         printList(network->rowMark->lens[i], network->rowMark->lens[i + 1]);
//     }
//     printf("Outputs :\n    ");
//     printList(network->rowMark->lens[network->rowMark->len - 2], network->rowMark->lens[network->rowMark->len - 1]);
// }

void printList(double* list, size_t len)
{
    printf("[");
    for (size_t i = 0; i < len; i++)
    {
        printf(" %f ", list[i]);
    }
    printf("]\n");
}

// void printNetwork(NeuralNetwork* network)
// {
//     printf("========Neural network (size %zu)=========\n", network->dataSize);
//     printf("Inputs :\n    ");
//     printList(network->activations->mark[0], network->activations->mark[1]);
//     printf("    Weights : \n     ");
//     printList(network->weights->mark[0], network->weights->mark[1]);
//     printf("Hiden rows : ");
//     size_t i = 1;
//     for(; i < network->dataSize - 2; i++)
//     {
//         printf("  Row %zu : \n", i);
//         printf("   Activation : \n    ");
//         printList(network->activations->mark[i], network->activations->mark[i + 1]);
//         printf("   Weights :\n    ");
//         printList(network->weights->mark[i], network->weights->mark[i + 1]);
//         printf("   Bias : \n    ");
//         printList(network->bias->mark[i - 1], network->bias->mark[i]);
//     }
//     printf("Outputs :\n   ");
//     i++;
//     printList(network->activations->mark[i], network->activations->mark[i + 1]);
//     printf("  Bias : \n    ");
//     printList(network->bias->mark[i - 1], network->bias->mark[i]);
//     printf("===END===\n");
// }


void printNetwork(NeuralNetwork* network)
{
    printf("=====Network=====\n");
    printf("Input : \n   ");
    printList(network->activations->data, network->inputNumber);

    printf("Weights :");
    printList(network->inputWeights->data, network->inputWeights->size);


    printf("Hiden row : \n");
    printf("  Activations : \n    ");
    printList(&(network->activations->data[network->inputNumber]), network->hidenNumber);
    printf("  Bias : \n    ");
    printList(network->bias->data, network->hidenNumber);

    printf("Weights :\n");
    printList(network->hidenWeights->data, network->hidenWeights->size);

    printf("Output : \n");
    printf("  Activations : \n    ");
    printList(&(network->activations->data[network->inputNumber + network->hidenNumber]), network->outputNumber);
    printf("  Bias : \n    ");
    printList(&(network->bias->data[network->hidenNumber]), network->outputNumber);


}
