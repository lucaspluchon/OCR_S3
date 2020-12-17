#ifndef LEARNING_H
#define LEARNING_H

#include "NeuralNetwork/headers/NeuralNetworkTools.h"

int ** loadAllResized(char** fileNames, size_t lowerBound, size_t upperBound);

double* findDelta(NeuralNetwork* network, double v, int* inputs, double* expected,
                  double *biasDeltaHiden, double *biasDeltaOut, double *deltaHiden, double *deltaOut);
void learn(NeuralNetwork* network, double v, int** allResized);
void fullTrain(NeuralNetwork * network, double v, size_t itteration, size_t hidenNumber, size_t lowerBound, size_t upperBound);
int testOnLetter(NeuralNetwork* network, int letter, int randPolice);
void testAllLetter(NeuralNetwork* network, size_t lowerBound, size_t upperBound);



#endif
