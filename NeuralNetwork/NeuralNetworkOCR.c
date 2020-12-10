#include "NeuralNetworkTools.h"
#include<stdlib.h>

int main()
{
    // Network* network = malloc(sizeof(Network));
    // RowMark* rowMark = malloc(sizeof(RowMark));
    // size_t lens[1] = {3};
    // GenerateNetwork(network, rowMark, 2, 3, 1, lens);
    // for(size_t i = 0; i < network->size; i++)
    // {
    //     network->data[i] = i;
    // }
    // printNetwork(network);
    

    // free(rowMark->lens);
    // free(rowMark);
    // free(network->data);
    // free(network);
    NeuralNetwork* network = malloc(sizeof(NeuralNetwork));

    // size_t lens[1] = {3};
    // size_t inputNumber = 2;
    // size_t outputNumber = 3;

    DataSet* activation = malloc(sizeof(DataSet));
    ListSet* li = malloc(sizeof(ListSet));
    li->size = 20;
    li->data = calloc(20, sizeof(double));
    for (size_t i = 0; i< 20; i++)
    {
        li->data[i] = i;
    }
    

    return 0;
}
