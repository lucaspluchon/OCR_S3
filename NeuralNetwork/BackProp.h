#ifndef BACK_PROP_H
#define BACK_PROP_H
#include"NeuralNetworkTools.h"


double delta(double error, double activation, double v);
double* outputError(NeuralNetwork* network, double* expected, double* res);
double hidenError(NeuralNetwork* network, size_t nodeIndex, double* outputError);
double* hidenErrors(NeuralNetwork* network, double* outputError, double* res);
double* outputWeightDelta(NeuralNetwork* network, double* errors, double v, double* res);
double* biasDelta(size_t len, double* errors, double v, double* res);
double* hidenWeightDelta(NeuralNetwork* network, double* errors, double v, double* res);

#endif
