#include<stdlib.h>

#ifndef NEURAL_NETWORK_TOOLS_H
#define NEURAL_NETWORK_TOOLS_H

typedef struct RowMark RowMark;
struct RowMark
{
    size_t len;
    double** lens;
};

typedef struct Network Network;
struct Network
{
    size_t size;
    RowMark* rowMark;
    double* data;
};

void GenerateNetwork(Network* network, RowMark* rowMark, size_t inputsNumber, size_t outputsNumber, size_t hidenRowNumber, size_t* hidenRowLen);
void printNetwork(Network* network);

#endif
