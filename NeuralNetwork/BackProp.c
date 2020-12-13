#include<err.h>
#include<stdio.h>

#include"NeuralNetworkTools.h"


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
    double res = sigmoideDerivate(network->activations->data[nodeIndex]);
    for (size_t i = 0; i < network->outputNumber; i++)
    {
        res += outputError[i] * weights[i * network->hidenNumber];
    }
    return res;
}


double* biasDelta(size_t len, double* errors, double v, double* res)
{
    for (size_t i = 0; i < len; i++)
    {
        res[i] = delta(errors[i], 1, v);
    }
    return res;
}

double* hidenWeightDelta(NeuralNetwork* network, double* errors, double v, double* res)
{
    for(size_t i = 0; i < network->outputNumber; i++)
    {
        for(size_t j = 0; j < network->hidenNumber; j++)
        {
            res[i + j] = delta(errors[i], network->activations->data[network->inputNumber + j], v);
            printf("error : %f  activation : %f", errors[i], network->activations->data[network->inputNumber + j]);
        }
    }
    return res;
}

