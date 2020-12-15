#include<stdio.h>
#include<stdlib.h>
#include<err.h>

#include"NeuralNetworkTools.h"


int writeData(NeuralNetwork* data)
{
    FILE *fp;
    fp = fopen("value", "w");
    if (fp != NULL)
    {
        fwrite(data->activations, sizeof(data->activations), 1, fp);
        fclose(fp);
        return 0;
    }
    return 1;
}


int readData(NeuralNetwork *data)
{
    FILE *fp;
    fp = fopen("value", "r");
    if (fp != NULL)
    {
        fread(data->activations, sizeof(data->activations), 1, fp);
        fclose(fp);
        return 0;
    }
    return 1;
}


int writeList(ListSet* l, char* name, char* listName)
{
    FILE *fp;
    fp = fopen(name, "w");
    if (fp != NULL)
    {
        fwrite(l, sizeof(ListSet), 1, fp);
        fclose(fp);
        FILE *fpl;
        fpl = fopen(listName, "w");
        if (fpl != NULL)
        {
            fwrite(l->data, sizeof(double) * l->size, 1, fpl);
            fclose(fpl);
            return 0;
        }
    }
    return 1;
}

ListSet* readList(char* name, char* listName)
{
    FILE *fp;
    fp = fopen(name, "r");
    if (fp != NULL)
    {
        ListSet* l = malloc(sizeof(ListSet));
        if (l == NULL)
            errx(1, "Memory allocation failed");
        fread(l, sizeof(ListSet), 1, fp);
        fclose(fp);
        FILE* fpl;
        fpl = fopen(listName, "r");
        if (fpl != NULL)
        {
            l->data = malloc(sizeof(double) * l->size);
            if (l->data == NULL)
                errx(1, "Memory allocation failed");
            fread(l->data, sizeof(double) * l->size, 1, fpl);
            fclose(fpl);
            return l;
        }
    }
    return NULL;
}

int writeNetwork(NeuralNetwork* network)
{
    FILE* netFp;
    netFp = fopen("network", "w");
    if (netFp == NULL)
        return 1;
    fwrite(network, sizeof(size_t) * 3, 1, netFp);
    fclose(netFp);
    if (writeList(network->activations, "activations", "activations_l") == 1)
        return 1;
    if(writeList(network->bias, "bias", "bias_l") == 1)
        return 1;
    if(writeList(network->hidenWeights, "hWeights", "hWeights_l") == 1)
        return 1;
    if(writeList(network->inputWeights, "iWeights", "iWeights_l") == 1)
        return 1;
    return 0;
}

NeuralNetwork* readNetwork()
{
    FILE* netFp;
    netFp = fopen("network", "r");
    if(netFp == NULL)
        return NULL;
    NeuralNetwork* network = malloc(sizeof(NeuralNetwork));
    if (network == NULL)
        errx(1, "Memory allocation failed");
    fread(network, sizeof(size_t) * 3, 1, netFp);

    network->activations = readList("activations", "activation_l");
    network->hidenWeights = readList("hWeights", "hWeights_l");
    network->inputWeights = readList("iWeights", "iWeights_l");
    network->bias = readList("bias", "bias_l");

    if (network->bias == NULL)
        printf("Unable to load bias\n");

    if (network->hidenWeights == NULL)
        printf("Unable to load hiden weights\n");

    if (network->inputWeights == NULL)
        printf("Unable to load input wieghts\n");

    if (network->activations == NULL)
        printf("Unable to load activations\n");

    return network;
}

