#include<stdlib.h>

#ifndef NEURAL_NETWORK_TOOLS_H
#define NEURAL_NETWORK_TOOLS_H

// typedef struct RowMark RowMark;
// struct RowMark
// {
//     size_t len;
//     double** lens;
// };

// typedef struct Network Network;
// struct Network
// {
//     size_t size;
//     RowMark* rowMark;
//     double* data;
// };

typedef struct ListSet ListSet;
struct ListSet
{
    size_t size;
    double* data;
};

typedef struct DataSet DataSet;
struct DataSet
{
    size_t size;
    ListSet* data;
    double** mark;
};

typedef struct NeuralNetwork NeuralNetwork;
struct NeuralNetwork
{
    size_t dataSize;
    DataSet* activations;
    DataSet* weights;
    DataSet* bias;
};


// void GenerateNetwork(Network* network, RowMark* rowMark, size_t inputsNumber, size_t outputsNumber, size_t hidenRowNumber, size_t* hidenRowLen);
void printNetwork(NeuralNetwork* network);

#endif
