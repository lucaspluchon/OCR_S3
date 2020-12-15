#include "NeuralNetworkTools.h"
#include<stdlib.h>
#include<stdio.h>
#include"ForwardProp.h"
#include"BackProp.h"
#include"FileManagment.h"


int main()
{

    NeuralNetwork* network = NULL;

    network = readNetwork();
    printNetwork(network);
    return 0;


    network = GenerateNetwork(2, 3, 2);

    readData(network);

    printNetwork(network);
 
    printNetwork(network);
    for(size_t i = 0; i < 200; i++)
    {
        network->activations->data[0] = 1;
        network->activations->data[1] = 0;
        forwardProp(network);

        double* exep = malloc(2 * sizeof(double));
        exep[0] = 1;
        exep[1] = 1;

        double* outError = calloc(2, sizeof(double));
        outputError(network, exep, outError);
        // printf("Output error\n");
        // printf("%f\n", *outError);

        double* hidError = calloc(3, sizeof(double));
        hidenErrors(network, outError, hidError);
        // printf("Hiden error\n");
        // printf("%f, %f\n", hidError[0], hidError[1]);

        double* bDelta = calloc(3, sizeof(double));
        double* bDelta2 = calloc(2, sizeof(double));
        biasDelta(3, hidError, 2, bDelta);
        biasDelta(2, outError, 2, bDelta2);

        // printf("Delta bias ; \n");
        // printf("%f ; %f ; %f\n", bDelta[0], bDelta[1], bDelta[2]);

        double* dOut = calloc(6, sizeof(double));
        outputWeightDelta(network, outError, 2, dOut);

        // printf("Delta out ; \n");
        // printf("%f ; %f\n", dOut[0], dOut[1]);
        
        double* dHid = calloc(6, sizeof(double));
        hidenWeightDelta(network, hidError, 2, dHid);

        // printf("Delta hid ; \n");
        // printf("%f ; %f ; %f ; %f\n", dHid[0], dHid[1], dHid[2], dHid[3]);
        free(outError);
        free(hidError);
 


        network->activations->data[0] = 1;
        network->activations->data[1] = 1;
        forwardProp(network);
        exep[0] = 0;
        exep[1] = 1;

        outError = calloc(2, sizeof(double));
        outputError(network, exep, outError);
        // printf("Output error\n");
        // printf("%f\n", *outError);

        hidError = calloc(3, sizeof(double));
        hidenErrors(network, outError, hidError);
        // printf("Hiden error\n");
        // printf("%f, %f\n", hidError[0], hidError[1]);

        biasDelta(3, hidError, 1, bDelta);
        biasDelta(2, outError, 1, bDelta2);

        // printf("Delta bias ; \n");
        // printf("%f ; %f ; %f\n", bDelta[0], bDelta[1], bDelta[2]);

        outputWeightDelta(network, outError, 2, dOut);

        // printf("Delta out ; \n");
        // printf("%f ; %f\n", dOut[0], dOut[1]);
        
        hidenWeightDelta(network, hidError, 2, dHid);

        // printf("Delta hid ; \n");
        // printf("%f ; %f ; %f ; %f\n", dHid[0], dHid[1], dHid[2], dHid[3]);
        free(outError);
        free(hidError);


        network->activations->data[0] = 0;
        network->activations->data[1] = 1;
        forwardProp(network);
        exep[0] = 1;
        exep[1] = 1;

        outError = calloc(2, sizeof(double));
        outputError(network, exep, outError);
        // printf("Output error\n");
        // printf("%f\n", *outError);

        hidError = calloc(3, sizeof(double));
        hidenErrors(network, outError, hidError);
        // printf("Hiden error\n");
        // printf("%f, %f\n", hidError[0], hidError[1]);

        biasDelta(3, hidError, 2, bDelta);
        biasDelta(2, outError, 2, bDelta2);

        // printf("Delta bias ; \n");
        // printf("%f ; %f ; %f\n", bDelta[0], bDelta[1], bDelta[2]);

        outputWeightDelta(network, outError, 2, dOut);

        // printf("Delta out ; \n");
        // printf("%f ; %f\n", dOut[0], dOut[1]);
        
        hidenWeightDelta(network, hidError, 2, dHid);

        // printf("Delta hid ; \n");
        // printf("%f ; %f ; %f ; %f\n", dHid[0], dHid[1], dHid[2], dHid[3]);
        free(outError);
        free(hidError);

        network->activations->data[0] = 0;
        network->activations->data[1] = 0;
        forwardProp(network);
        exep[0] = 0;
        exep[1] = 0;

        outError = calloc(2, sizeof(double));
        outputError(network, exep, outError);
        // printf("Output error\n");
        // printf("%f\n", *outError);

        hidError = calloc(3, sizeof(double));
        hidenErrors(network, outError, hidError);
        // printf("Hiden error\n");
        // printf("%f, %f\n", hidError[0], hidError[1]);

        biasDelta(3, hidError, 2, bDelta);
        biasDelta(2, outError, 2, bDelta2);

        // printf("Delta bias ; \n");
        // printf("%f ; %f ; %f\n", bDelta[0], bDelta[1], bDelta[2]);

        outputWeightDelta(network, outError, 2, dOut);

        // printf("Delta out ; \n");
        // printf("%f ; %f\n", dOut[0], dOut[1]);
        
        hidenWeightDelta(network, hidError, 2, dHid);

        // printf("Delta hid ; \n");
        // printf("%f ; %f ; %f ; %f\n", dHid[0], dHid[1], dHid[2], dHid[3]);
        free(outError);
        free(hidError);
        free(exep);
 

        network->inputWeights->data[0] += dHid[0];
        network->inputWeights->data[1] += dHid[1];
        network->inputWeights->data[2] += dHid[2];
        network->inputWeights->data[3] += dHid[3];
        network->inputWeights->data[4] += dHid[4];
        network->inputWeights->data[5] += dHid[5];

        network->hidenWeights->data[0] += dOut[0];
        network->hidenWeights->data[1] += dOut[1];
        network->hidenWeights->data[2] += dOut[2];
        network->hidenWeights->data[3] += dOut[3];
        network->hidenWeights->data[4] += dOut[4];
        network->hidenWeights->data[5] += dOut[5];

        network->bias->data[0] += bDelta[0];
        network->bias->data[1] += bDelta[1];
        network->bias->data[2] += bDelta[2];
        network->bias->data[3] += bDelta2[0];
        network->bias->data[4] += bDelta2[1];

        // if (i > 100)
        // {
        //     printf("\n\ni = %zu\n", i);
        //     printNetwork(network);
        //     printf("Delta hiden : %f ; %f ; %f ; %f\n", dHid[0], dHid[1], dHid[2], dHid[3]);
        //     printf("Delta hiden : %f ; %f\n", dOut[0], dOut[1]);
        //     printf("Delta bias : %f ; %f ; %f\n\n", bDelta[0], bDelta[1], bDelta[2]);

        // }

        free(dHid);
        free(dOut);
        free(bDelta);
        free(bDelta2);
    }

    printNetwork(network);
    writeNetwork(network);

    // network->activations->data[0] = 0;
    // network->activations->data[1] = 0;
    // forwardProp(network);
    // printNetwork(network);
    // network->activations->data[0] = 1;
    // network->activations->data[1] = 0;
    // forwardProp(network);
    // printNetwork(network);
    // network->activations->data[0] = 0;
    // network->activations->data[1] = 1;
    // forwardProp(network);
    // printNetwork(network);
    // network->activations->data[0] = 1;
    // network->activations->data[1] = 1;
    // forwardProp(network);
    // printNetwork(network);



    // writeData(network);
    // freeNetwork(network);


    // ListSet* l = NULL;
    // ListSet* l = malloc(sizeof(ListSet));
    // l->size = 5;
    // l->data = malloc(sizeof(double) * 5);
    // l->data[0] = 1;
    // l->data[1] = 2;
    // l->data[2] = 3;
    // l->data[3] = 4;
    // l->data[4] = 5;

    // l = readList("activation", "activation_l");
    // printList(l->data, l->size);
    // printf("%lu", sizeof(*l));
    // writeList(l, "activation", "activation_l");

    return 0;
}
