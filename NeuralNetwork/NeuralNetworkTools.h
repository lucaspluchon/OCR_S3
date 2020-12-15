#include<stdlib.h>

#ifndef NEURAL_NETWORK_TOOLS_H
#define NEURAL_NETWORK_TOOLS_H


typedef struct ListSet ListSet;
struct ListSet
{
    size_t size;
    double* data;
};

double sigmoid(double x);
double sigmoideDerivate(double x);

typedef struct NeuralNetwork NeuralNetwork;
struct NeuralNetwork
{
    size_t inputNumber;
    size_t hidenNumber;
    size_t outputNumber;
    ListSet* activations;
    ListSet* inputWeights;
    ListSet* hidenWeights;
    ListSet* bias;
};

double randd();

void freeNetwork(NeuralNetwork* network);
NeuralNetwork* GenerateNetwork(size_t inputNumber, size_t hidenNumber, size_t outputNumber);
void printList(double* list, size_t len);
void printNetwork(NeuralNetwork* network);

#endif
