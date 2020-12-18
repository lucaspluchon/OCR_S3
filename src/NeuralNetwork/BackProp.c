#include <err.h>
#include <stdio.h>

#include "headers/NeuralNetworkTools.h"


double delta(double error, double activation, double v)
{
    return error * activation * v;
}


double* outputError(NeuralNetwork* network, double* expected, double* res)
{
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
    double res = 0;
    for (size_t i = 0; i < network->outputNumber; i++)
    {
        res += outputError[i] * weights[i * network->hidenNumber];
    }
    return res * sigmoideDerivate(network->activations->data[nodeIndex]);
}

double* hidenErrors(NeuralNetwork* network, double* outputError, double* res)
{
    for(size_t i = 0; i < network->hidenNumber; i++)
    {
        res[i] = hidenError(network, network->inputNumber + i, outputError);
    }
    return res;
}

double* biasDelta(size_t len, double* errors, double v, double* res)
{
    for (size_t i = 0; i < len; i++)
    {
        res[i] += delta(errors[i], 1, v);
    }
    return res;
}

double* outputWeightDelta(NeuralNetwork* network, double* errors, double v, double* res)
{
    for(size_t i = 0; i < network->outputNumber; i++)
    {
        for(size_t j = 0; j < network->hidenNumber; j++)
        {
            res[(i * network->hidenNumber) + j] += delta(errors[i], network->activations->data[network->inputNumber + j], v);
            // printf("error : %f  activation : %f\n", errors[i], network->activations->data[network->inputNumber + j]);
        }
    }
    return res;
}

double* hidenWeightDelta(NeuralNetwork* network, double* errors, double v, double* res)
{
    for(size_t i = 0; i < network->hidenNumber; i++)
    {
        for (size_t j = 0; j < network->inputNumber; j++)
        {
            res[(i * network->inputNumber) + j] += delta(errors[i], network->activations->data[j], v);
            // printf("error : %f  activation : %f\n", errors[i], network->activations->data[j]);
        }
    }
    return res;
}

