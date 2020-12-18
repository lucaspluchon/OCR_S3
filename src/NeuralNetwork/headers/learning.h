#ifndef LEARNING_H
#define LEARNING_H

#include "NeuralNetworkTools.h"


double* findDelta(NeuralNetwork* network, double v, int* inputs, double* expected,
                  double *biasDeltaHiden, double *biasDeltaOut, double *deltaHiden, double *deltaOut);
void learn(NeuralNetwork* network, double v, int** allResized);
int ** loadAllResized(char** fileNames, size_t outputNumber);
void fullTrain(NeuralNetwork * network, double v, size_t itteration);



#endif
