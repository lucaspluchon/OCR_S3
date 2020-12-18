#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <err.h>
#include "headers/NeuralNetworkTools.h"

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


NeuralNetwork* GenerateNetwork(size_t inputNumber, size_t hidenNumber, size_t outputNumber, double* asciiOutputs)
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

    network->asciiOutputs = malloc(sizeof(ListSet));
    if(network->asciiOutputs == NULL)
        errx(1, "Memory allocation failed");
    network->asciiOutputs->size = outputNumber;
    network->asciiOutputs->data = malloc(sizeof(double) * outputNumber);
    if(network->asciiOutputs->data == NULL)
        errx(1, "Memory allocation failed");
    for(size_t i = 0; i < outputNumber; i++)
    {
        network->asciiOutputs->data[i] = asciiOutputs[i];
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

    free(network->asciiOutputs->data);
    free(network->asciiOutputs);

    free(network);

}



void printList(double* list, size_t len)
{
    printf("[");
    for (size_t i = 0; i < len; i++)
    {
        printf(" %f ", list[i]);
    }
    printf("]\n");
}



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
    printf("Ascii outputs : \n");
    printList(network->asciiOutputs->data, network->outputNumber);

}
