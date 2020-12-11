#include<err.h>

#include"NeuralNetworkTools.h"


double delta(double error, double activation, double v)
{
    return error * activation * v;
}


double* outputError(NeuralNetwork* network, double* expected)
{
    double* res = malloc(sizeof(double) * network->outputNumber);
    if (res == NULL)
        errx(1, "Memory allocation failed");
    double* outputs = &(network->activations->data[network->inputNumber + network->hidenNumber]);
    for (size_t i = 0; i < network->outputNumber; i++)
    {
        res[i] = (expected[i] - outputs[i]) * sigmoideDerivate(outputs[i]);
    }
    return res;
}

double hidenError(NeuralNetwork* network, size_t nodeIndex, double* outputError)
{
    double* weights = &(network->hidenWeights->data[nodeIndex - network->inputNumber]);
    double res = sigmoideDerivate(network->activations->data[nodeIndex]);
    for (size_t i = 0; i < network->outputNumber; i++)
    {
        res += outputError[i] + weights[i * network->hidenNumber];
        weights[i * network->hidenNumber] = nodeIndex;
    }
    return res;
}

// double* hideneErrors(NeuralNetwork* network)
