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
    size_t inputNumber;
    size_t hidenNumber;
    size_t outputNumber;
    ListSet* activations;
    ListSet* weights;
    ListSet* bias;
};

void freeNetwork(NeuralNetwork* network);
NeuralNetwork* GenerateNetwork(size_t inputNumber, size_t hidenNumber, size_t outputNumber);
void printNetwork(NeuralNetwork* network);

#endif
