#ifndef FILEMANAGMENT_H
#define FILEMANAGMENT_H
#include"NeuralNetworkTools.h"
int writeData(NeuralNetwork* data);
int readData(NeuralNetwork *data);
int writeList(ListSet* l, char* name, char* listName);
ListSet* readList(char* name, char* listName);
int writeNetwork(NeuralNetwork* network);
NeuralNetwork* readNetwork();



#endif
