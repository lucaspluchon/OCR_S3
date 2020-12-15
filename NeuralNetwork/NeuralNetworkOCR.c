#include "NeuralNetworkTools.h"
#include<stdlib.h>
#include<stdio.h>
#include"ForwardProp.h"
#include"BackProp.h"

int main()
{

    NeuralNetwork* network = NULL;


    network = GenerateNetwork(2, 2, 1);

    printNetwork(network);
 
    printNetwork(network);
    for(size_t i = 0; i < 2000; i++)
    {
        network->activations->data[0] = 1;
        network->activations->data[1] = 0;
        forwardProp(network);
        double ex = 1;
        double* exep = &ex;

        double* outError = calloc(1, sizeof(double));
        outputError(network, exep, outError);
        // printf("Output error\n");
        // printf("%f\n", *outError);

        double* hidError = calloc(2, sizeof(double));
        hidenErrors(network, outError, hidError);
        // printf("Hiden error\n");
        // printf("%f, %f\n", hidError[0], hidError[1]);

        double* bDelta = calloc(2, sizeof(double));
        double* bDelta2 = calloc(1, sizeof(double));
        biasDelta(2, hidError, 1, bDelta);
        biasDelta(1, outError, 1, bDelta2);

        // printf("Delta bias ; \n");
        // printf("%f ; %f ; %f\n", bDelta[0], bDelta[1], bDelta[2]);

        double* dOut = calloc(2, sizeof(double));
        outputWeightDelta(network, outError, 1, dOut);

        // printf("Delta out ; \n");
        // printf("%f ; %f\n", dOut[0], dOut[1]);
        
        double* dHid = calloc(4, sizeof(double));
        hidenWeightDelta(network, hidError, 1, dHid);

        // printf("Delta hid ; \n");
        // printf("%f ; %f ; %f ; %f\n", dHid[0], dHid[1], dHid[2], dHid[3]);
        free(outError);
        free(hidError);
 


        network->activations->data[0] = 1;
        network->activations->data[1] = 1;
        forwardProp(network);
        ex = 0;

        outError = calloc(1, sizeof(double));
        outputError(network, exep, outError);
        // printf("Output error\n");
        // printf("%f\n", *outError);

        hidError = calloc(2, sizeof(double));
        hidenErrors(network, outError, hidError);
        // printf("Hiden error\n");
        // printf("%f, %f\n", hidError[0], hidError[1]);

        biasDelta(2, hidError, 1, bDelta);
        biasDelta(1, outError, 1, bDelta2);

        // printf("Delta bias ; \n");
        // printf("%f ; %f ; %f\n", bDelta[0], bDelta[1], bDelta[2]);

        outputWeightDelta(network, outError, 1, dOut);

        // printf("Delta out ; \n");
        // printf("%f ; %f\n", dOut[0], dOut[1]);
        
        hidenWeightDelta(network, hidError, 1, dHid);

        // printf("Delta hid ; \n");
        // printf("%f ; %f ; %f ; %f\n", dHid[0], dHid[1], dHid[2], dHid[3]);
        free(outError);
        free(hidError);


        network->activations->data[0] = 0;
        network->activations->data[1] = 1;
        forwardProp(network);
        ex = 1;

        outError = calloc(1, sizeof(double));
        outputError(network, exep, outError);
        // printf("Output error\n");
        // printf("%f\n", *outError);

        hidError = calloc(2, sizeof(double));
        hidenErrors(network, outError, hidError);
        // printf("Hiden error\n");
        // printf("%f, %f\n", hidError[0], hidError[1]);

        biasDelta(2, hidError, 1, bDelta);
        biasDelta(1, outError, 1, bDelta2);

        // printf("Delta bias ; \n");
        // printf("%f ; %f ; %f\n", bDelta[0], bDelta[1], bDelta[2]);

        outputWeightDelta(network, outError, 1, dOut);

        // printf("Delta out ; \n");
        // printf("%f ; %f\n", dOut[0], dOut[1]);
        
        hidenWeightDelta(network, hidError, 1, dHid);

        // printf("Delta hid ; \n");
        // printf("%f ; %f ; %f ; %f\n", dHid[0], dHid[1], dHid[2], dHid[3]);
        free(outError);
        free(hidError);

        network->activations->data[0] = 0;
        network->activations->data[1] = 0;
        forwardProp(network);
        ex = 0;

        outError = calloc(1, sizeof(double));
        outputError(network, exep, outError);
        // printf("Output error\n");
        // printf("%f\n", *outError);

        hidError = calloc(2, sizeof(double));
        hidenErrors(network, outError, hidError);
        // printf("Hiden error\n");
        // printf("%f, %f\n", hidError[0], hidError[1]);

        biasDelta(2, hidError, 1, bDelta);
        biasDelta(1, outError, 1, bDelta2);

        // printf("Delta bias ; \n");
        // printf("%f ; %f ; %f\n", bDelta[0], bDelta[1], bDelta[2]);

        outputWeightDelta(network, outError, 1, dOut);

        // printf("Delta out ; \n");
        // printf("%f ; %f\n", dOut[0], dOut[1]);
        
        hidenWeightDelta(network, hidError, 1, dHid);

        // printf("Delta hid ; \n");
        // printf("%f ; %f ; %f ; %f\n", dHid[0], dHid[1], dHid[2], dHid[3]);
        free(outError);
        free(hidError);
 

        network->inputWeights->data[0] += dHid[0];
        network->inputWeights->data[1] += dHid[1];
        network->inputWeights->data[2] += dHid[2];
        network->inputWeights->data[3] += dHid[3];

        network->hidenWeights->data[0] += dOut[0];
        network->hidenWeights->data[1] += dOut[1];

        network->bias->data[0] += bDelta[0];
        network->bias->data[1] += bDelta[1];
        network->bias->data[2] += *bDelta2;

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

    network->activations->data[0] = 0;
    network->activations->data[1] = 0;
    forwardProp(network);
    printNetwork(network);
    network->activations->data[0] = 1;
    network->activations->data[1] = 0;
    forwardProp(network);
    printNetwork(network);
    network->activations->data[0] = 0;
    network->activations->data[1] = 1;
    forwardProp(network);
    printNetwork(network);
    network->activations->data[0] = 1;
    network->activations->data[1] = 1;
    forwardProp(network);
    printNetwork(network);



    freeNetwork(network);

    return 0;
}
