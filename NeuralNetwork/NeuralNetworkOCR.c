#include "NeuralNetworkTools.h"
#include<stdlib.h>

int main()
{
    Network* network = malloc(sizeof(Network));
    RowMark* rowMark = malloc(sizeof(RowMark));
    size_t lens[1] = {3};
    GenerateNetwork(network, rowMark, 2, 3, 1, lens);
    for(size_t i = 0; i < network->size; i++)
    {
        network->data[i] = i;
    }
    printNetwork(network);
    

    free(rowMark->lens);
    free(rowMark);
    free(network->data);
    free(network);
    return 0;
}
