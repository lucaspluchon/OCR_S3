#include "NeuralNetworkTools.h"
#include<stdlib.h>
#include<stdio.h>
#include"ForwardProp.h"
#include"BackProp.h"

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
    // NeuralNetwork* network = malloc(sizeof(NeuralNetwork));

    // // size_t lens[1] = {3};
    // // size_t inputNumber = 2;
    // // size_t outputNumber = 3;

    // DataSet* activation = malloc(sizeof(DataSet));
    // ListSet* li = malloc(sizeof(ListSet));
    // li->size = 20;
    // li->data = calloc(20, sizeof(double));
    // for (size_t i = 0; i< 20; i++)
    // {
    //     li->data[i] = i;
    // }

    NeuralNetwork* network = NULL;

    network = GenerateNetwork(3, 3, 1);
    
    // printNetwork(network);

    // double i = 0;
    // for(size_t j = 0;j < network->activations->size; j++)
    // {
    //     network->activations->data[j] = ++i;
    // }
    // for(size_t j = 0;j < network->weights->size; j++)
    // {
    //     network->weights->data[j] = ++i;
    // }
    // for(size_t j = 0;j < network->bias->size; j++)
    // {
    //     network->bias->data[j] = ++i;
    // }
    forwardProp(network);
    printNetwork(network);
    double* hDelta = calloc(network->hidenNumber * network->outputNumber, sizeof(double));
    double* iDelta = calloc(network->hidenNumber * network->inputNumber, sizeof(double));
    double* bdelta = calloc(network->hidenNumber + network->outputNumber, sizeof(double));

    for(size_t i = 0; i < 1000; i++)
    {


        network->activations->data[0] = 1;
        network->activations->data[1] = 1;
        network->activations->data[2] = 1;
        forwardProp(network);
        double ex = 1;
        double* exep = &ex;
        double* error = calloc(network->outputNumber, sizeof(double));
        error = outputError(network, exep, error);

        double* herror = calloc(network->hidenNumber, sizeof(double));
        herror = hidenErrors(network, error, herror);
        double* res = calloc(network->outputNumber * network->hidenNumber, sizeof(double));
        outputWeightDelta(network, error, 1, res);

        double* resH = calloc(network->inputNumber * network->hidenNumber, sizeof(double));
        resH = hidenWeightDelta(network, herror, 1, resH);

        double* bres = calloc(network->hidenNumber + network->outputNumber, sizeof(double));
        biasDelta(network->hidenNumber, resH, 1, bres);
        biasDelta(network->outputNumber, resH, 1, &(bres[network->hidenNumber]));

        for (size_t i = 0; i < network->outputNumber * network->hidenNumber; i++)
        {
            hDelta[i] += res[i];
        }
        for (size_t i = 0; i < network->inputNumber * network->hidenNumber; i++)
        {
            iDelta[i] += resH[i];
        }
        for (size_t i = 0; i < network->outputNumber + network->hidenNumber; i++)
        {
            bdelta[i] += bres[i];
        }


        network->activations->data[0] = 0;
        network->activations->data[1] = 1;
        network->activations->data[2] = 1;
        forwardProp(network);
        ex = 0;
        error = outputError(network, exep, error);

        herror = hidenErrors(network, error, herror);
        outputWeightDelta(network, error, 1, res);


        resH = hidenWeightDelta(network, herror, 1, resH);


        biasDelta(network->hidenNumber, resH, 1, bres);
        biasDelta(network->outputNumber, resH, 1, &(bres[network->hidenNumber]));

        for (size_t i = 0; i < network->outputNumber * network->hidenNumber; i++)
        {
            hDelta[i] += res[i];
        }
        for (size_t i = 0; i < network->inputNumber * network->hidenNumber; i++)
        {
            iDelta[i] += resH[i];
        }
        for (size_t i = 0; i < network->outputNumber + network->hidenNumber; i++)
        {
            bdelta[i] += bres[i];
        }
        network->activations->data[0] = 1;
        network->activations->data[1] = 0;
        network->activations->data[2] = 0;
        forwardProp(network);
        ex = 1;
        error = outputError(network, exep, error);

        herror = hidenErrors(network, error, herror);
        outputWeightDelta(network, error, 1, res);


        resH = hidenWeightDelta(network, herror, 1, resH);


        biasDelta(network->hidenNumber, resH, 1, bres);
        biasDelta(network->outputNumber, resH, 1, &(bres[network->hidenNumber]));

        for (size_t i = 0; i < network->outputNumber * network->hidenNumber; i++)
        {
            hDelta[i] += res[i];
        }
        for (size_t i = 0; i < network->inputNumber * network->hidenNumber; i++)
        {
            iDelta[i] += resH[i];
        }
        for (size_t i = 0; i < network->outputNumber + network->hidenNumber; i++)
        {
            bdelta[i] += bres[i];
        }
        network->activations->data[0] = 0;
        network->activations->data[1] = 1;
        network->activations->data[1] = 0;
        forwardProp(network);
        ex = 0;
        error = outputError(network, exep, error);

        herror = hidenErrors(network, error, herror);
        outputWeightDelta(network, error, 1, res);


        resH = hidenWeightDelta(network, herror, 1, resH);


        biasDelta(network->hidenNumber, resH, 1, bres);
        biasDelta(network->outputNumber, resH, 1, &(bres[network->hidenNumber]));

        for (size_t i = 0; i < network->outputNumber * network->hidenNumber; i++)
        {
            hDelta[i] += res[i];
        }
        for (size_t i = 0; i < network->inputNumber * network->hidenNumber; i++)
        {
            iDelta[i] += resH[i];
        }
        for (size_t i = 0; i < network->outputNumber + network->hidenNumber; i++)
        {
            bdelta[i] += bres[i];
        }
        free(bres);
        free(res);
        free(resH);
        for (size_t i = 0; i < network->outputNumber * network->hidenNumber; i++)
        {
            network->hidenWeights->data[i] += hDelta[i];
        }
        for (size_t i = 0; i < network->inputNumber * network->hidenNumber; i++)
        {
            network->inputWeights->data[i] += iDelta[i];
        }
        for (size_t i = 0; i < network->outputNumber + network->hidenNumber; i++)
        {
            network->bias->data[i] = bdelta[i];
        }

    }

    network->activations->data[0] = 1;
    network->activations->data[1] = 0;
    forwardProp(network);
    printNetwork(network);
    printf("Res for 0 0 %f\n", network->activations->data[network->inputNumber + network->hidenNumber + network->outputNumber - 1]);
    // double* ex = calloc(7, sizeof(double));
    // ex[2] = 1;
    // printf("*");
    // hidenError(network, 5, error);
    // hidenError(network, 6, error);
    // hidenError(network, 7, error);
    // hidenError(network, 8, error);
    // hidenError(network, 9, error);
    // hidenError(network, 10, error);

    // printNetwork(network);

    // free(ex);
    // free(error);
    freeNetwork(network);

    return 0;
}
