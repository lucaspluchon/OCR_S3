#include <math.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
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


void GenerateNetwork(Network* network, RowMark* rowMark, size_t inputsNumber, size_t outputsNumber, size_t hidenRowNumber, size_t* hidenRowLen)
{

    size_t size = 0;
    for(size_t i = 0; i < hidenRowNumber; i++)
    {
        size += hidenRowLen[i];
    }
    size += inputsNumber + outputsNumber;

    //Size init
    network = malloc(sizeof(size_t));
    network->size = size;

    //Row mark init
    rowMark = malloc(sizeof(size_t));
    rowMark->len = hidenRowNumber;

    rowMark->lens = malloc(sizeof(double*) * (hidenRowNumber + 3));

    //Data init
    network->data = calloc(size, sizeof(double));

    //Row mark valuation
    size_t i = 1;
    rowMark->lens[0] = network->data;
    size_t sum = inputsNumber;
    for(; i < hidenRowNumber; i++)
    {
        rowMark->lens[i] = &(network->data[sum]);
        sum += hidenRowLen[i];
    }
    rowMark->lens[i] = &(network->data[sum]);
    rowMark->lens[i + 1] = &(network->data[sum + outputsNumber]);
    network->rowMark = rowMark;

}


void printList(double* list, double* end)
{
    printf("[");
    for(double* p = list; p < end; p++)
    {
        printf(" %f ", *p);
    }
    printf("]\n");
}

void printNetwork(Network* network)
{
    printf("=========Network(size %zu)=========\n", network->size);
    printf("Inputs :\n    ");
    printList(network->rowMark->lens[0], network->rowMark->lens[1]);
    for(size_t i = 1; i < network->rowMark->len - 2; i++)
    {
        printList(network->rowMark->lens[i], network->rowMark->lens[i + 1]);
    }
    printf("Outputs :\n    ");
    printList(network->rowMark->lens[network->rowMark->len - 1], network->rowMark->lens[network->rowMark->len]);
}
