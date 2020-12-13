#ifndef BACK_PROP_H
#define BACK_PROP_H
#include"NeuralNetworkTools.h"


double delta(double error, double activation, double v);
double* outputError(NeuralNetwork* network, double* expected);
double hidenError(NeuralNetwork* network, size_t nodeIndex, double* outputError);
double* hidenWeightDelta(NeuralNetwork* network, double* errors, double v, double* res);
double* biasDelta(size_t len, double* errors, double v, double* res)

#endif
