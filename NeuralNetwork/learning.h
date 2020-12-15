#ifndef LEARNING_H
#define LEARNING_H

#include "NeuralNetworkTools.h"

double* findDelta(NeuralNetwork* network, double v, int* inputs, double* expected,double *biasDeltaHiden, double *biasDeltaOut, double *deltaHiden, double *deltaOut);
void learn(NeuralNetwork* network, int LowerBound, int UpperBound, double v, char** fileNames);
NeuralNetwork* fullTrain(double v, size_t itteration, size_t hidenNumber, size_t lowerBound, size_t upperBound);



#endif
