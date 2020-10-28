#include<stdlib.h>
#include<stdio.h>

#include"BuiltinsNeuralNetworks.h"
#include"BackPropagation.h"
#include"FileManagment.h"
///////////////////////////////
//////DEMO FILE TEMPORARY//////
///////////////////////////////
void DemoNeural()
{
    NetworkData data = 
    {
        .x = 1,
        .y = 0,
        .excpect = 1,
        .activations = {0, 0},
        .weights = {randd(), randd(), randd(), randd(), randd()},
        .bias = {randd(), randd()}
    };

    Node *h;

    h = malloc(sizeof(*h));

    h->bias = &data.bias[0];
    h->activation = &data.activations[0];
    h->neuronsLen = 4;

    h->neurons = malloc(sizeof(double *) * 4);
    
    h->neurons[0] = &data.x;
    h->neurons[1] = &data.weights[0];
    h->neurons[2] = &data.y;
    h->neurons[3] = &data.weights[1];

    Node *z;

    z = malloc(sizeof(*z));

    z->bias = &data.bias[1];
    z->activation = &data.activations[1];
    z->neuronsLen = 6;

    z->neurons = malloc(sizeof(double *) * 6);

    z->neurons[0] = &data.x;
    z->neurons[1] = &data.weights[2];
    z->neurons[2] = &data.activations[0];
    z->neurons[3] = &data.weights[3];
    z->neurons[4] = &data.y;
    z->neurons[5] = &data.weights[4];


    printf("\n=====Network initialized with random values=====\n");
    printNetwork(h, z, &data);
    printf("\n=====Learning...=====\n");
    learnAverage(h, z, &data, 1.5, 400);

    printf("\n=====Network after learning with v = 1.5 and 400 iterations=====\n");
    printNetwork(h, z, &data);

    printf("\n=====Results=====\n");
    data.x = 1;
    data.y = 1;
    updateTreeNode(h, z);
    printRes(*(z->activation), 1, 1);

    data.x = 0;
    data.y = 0;
    updateTreeNode(h, z);
    printRes(*(z->activation), 0, 0);

    data.x = 1;
    data.y = 0;
    updateTreeNode(h, z);
    printRes(*(z->activation), 1, 0);

    data.x = 0;
    data.y = 1;
    updateTreeNode(h, z);
    printRes(*(z->activation), 0, 1);

    writeData(&data);

    free(h->neurons);
    free(z->neurons);
    free(h);
    free(z);
}

void demoWithLoad()
{
    NetworkData data;

    if (readData(&data) == 1)
    {
        printf("Unable to load file 'value' abort procces");
        return;
    }

    Node *h;

    h = malloc(sizeof(*h));

    h->bias = &data.bias[0];
    h->activation = &data.activations[0];
    h->neuronsLen = 4;

    h->neurons = malloc(sizeof(double *) * 4);
    
    h->neurons[0] = &data.x;
    h->neurons[1] = &data.weights[0];
    h->neurons[2] = &data.y;
    h->neurons[3] = &data.weights[1];

    Node *z;

    z = malloc(sizeof(*z));

    z->bias = &data.bias[1];
    z->activation = &data.activations[1];
    z->neuronsLen = 6;

    z->neurons = malloc(sizeof(double *) * 6);

    z->neurons[0] = &data.x;
    z->neurons[1] = &data.weights[2];
    z->neurons[2] = &data.activations[0];
    z->neurons[3] = &data.weights[3];
    z->neurons[4] = &data.y;
    z->neurons[5] = &data.weights[4];

    printf("\n=====Network after loading data=====\n");
    printNetwork(h, z, &data);

    printf("\n=====Results=====\n");
    data.x = 1;
    data.y = 1;
    updateTreeNode(h, z);
    printRes(*(z->activation), 1, 1);

    data.x = 0;
    data.y = 0;
    updateTreeNode(h, z);
    printRes(*(z->activation), 0, 0);

    data.x = 1;
    data.y = 0;
    updateTreeNode(h, z);
    printRes(*(z->activation), 1, 0);

    data.x = 0;
    data.y = 1;
    updateTreeNode(h, z);
    printRes(*(z->activation), 0, 1);

    writeData(&data);

    free(h->neurons);
    free(z->neurons);
    free(h);
    free(z);
}


