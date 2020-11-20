#include "NeuralNetworkTools.h"
#include<stdlib.h>

int main()
{
    Network* network = NULL;
    size_t lens[1] = {3};
    GenerateNetwork(network, 2, 3, 1, lens);

    free(network->rowMark->lens);
    free(network->rowMark);
    free(network->data);
    free(network);
    return 0;
}
