#include <stdlib.h>
#include <stdio.h>
#include <err.h>

#include "headers/NeuralNetworkTools.h"


void updateNode(NeuralNetwork* network, size_t nodeIndex)
{
    if (nodeIndex < network->inputNumber) 
        errx(1, "Bad node");
    double* weights = NULL;
    size_t len = 0;
    double* activations = NULL;
    double res = network->bias->data[nodeIndex - network->inputNumber];
    if (nodeIndex >= network->inputNumber + network->hidenNumber)
    {
        weights = &(network->hidenWeights->data[(nodeIndex - (network->inputNumber + network->hidenNumber)) * network->hidenNumber]);
        activations = &(network->activations->data[network->inputNumber]);
        len = network->hidenNumber;

    }
    else if (nodeIndex < network->inputNumber + network->hidenNumber)
    {
        weights = &(network->inputWeights->data[(nodeIndex - network->inputNumber) * network->inputNumber]);
        activations = network->activations->data;
        len = network->inputNumber;
    }

    for (size_t i = 0; i < len; i++)
    {
        res += activations[i] * weights[i];
    }

    network->activations->data[nodeIndex] = sigmoid(res);

}

void forwardProp(NeuralNetwork* network)
{
    for (size_t i = network->inputNumber; i < network->inputNumber + network->hidenNumber + network->outputNumber; i++)
    {
        updateNode(network, i);
    }
}
