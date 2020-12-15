#ifndef FILEMANAGMENT_H
#define FILEMANAGMENT_H
#include"NeuralNetworkTools.h"
int writeData(NeuralNetwork* data);
int readData(NeuralNetwork *data);
int writeList(ListSet* l, char* name, char* listName);
int readList(ListSet* l, char* name, char* listName);



#endif
