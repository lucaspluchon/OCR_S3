#include "NeuralNetworkTools.h"
#include<stdlib.h>

int main()
{
    Network* network = NULL;
    RowMark* rowMark = NULL;
    size_t lens[1] = {3};
    GenerateNetwork(network, rowMark, 2, 3, 1, lens);


    free(network->rowMark->lens);
    free(rowMark->lens);
    free(rowMark);
    free(network->data);
    free(network);
    return 0;
}
