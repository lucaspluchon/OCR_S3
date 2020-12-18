#include<stdio.h>
#include<stdlib.h>
#include<err.h>

#include "headers/NeuralNetworkTools.h"



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
    netFp = fopen("save/network.save", "w");
    if (netFp == NULL)
        return 1;
    fwrite(network, sizeof(size_t) * 4, 1, netFp);
    fclose(netFp);
    if (writeList(network->activations, "save/activations.save", "save/activations_l.save") == 1)
        return 1;
    if(writeList(network->bias, "save/bias.save", "save/bias_l.save") == 1)
        return 1;
    if(writeList(network->hidenWeights, "save/hWeights.save", "save/hWeights_l.save") == 1)
        return 1;
    if(writeList(network->inputWeights, "save/iWeights.save", "save/iWeights_l.save") == 1)
        return 1;
    if(writeList(network->asciiOutputs, "save/outAscii.save", "save/outAscii_l.save") == 1)
        return 1;
    return 0;
}

NeuralNetwork* readNetwork()
{
    FILE* netFp;
    netFp = fopen("save/network.save", "r");
    if(netFp == NULL)
        return NULL;
    NeuralNetwork* network = malloc(sizeof(NeuralNetwork));
    if (network == NULL)
        errx(1, "Memory allocation failed");
    fread(network, sizeof(size_t) * 4, 1, netFp);

    network->activations = readList("save/activations.save", "save/activations_l.save");
    network->hidenWeights = readList("save/hWeights.save", "save/hWeights_l.save");
    network->inputWeights = readList("save/iWeights.save", "save/iWeights_l.save");
    network->bias = readList("save/bias.save", "save/bias_l.save");
    network->asciiOutputs = readList("save/outAscii.save", "save/outAscii_l.save");

    if (network->bias == NULL)
        printf("Unable to load bias\n");

    if (network->hidenWeights == NULL)
        printf("Unable to load hiden weights\n");

    if (network->inputWeights == NULL)
        printf("Unable to load input wieghts\n");

    if (network->activations == NULL)
        printf("Unable to load activations\n");

    if (network->asciiOutputs == NULL)
        printf("Unable to load ascii output\n");

    return network;
}

