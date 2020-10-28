#include<stdlib.h>
#include <math.h>
#include"BuiltinsNeuralNetworks.h"
#include"BackPropagation.h"
#include"FileManagment.h"


void entry();

// int main()
// {
//     entry();
// }

/*Inputs : x = 0.000000
y = 0.000000
h = {
	activation = 1.000000
	bias = 114.965368
	weight to x = -195.959417
	weight to y = -197.869329
}

z = {
	activation = 0.000000
	bias = 231.704368
	weight to x = -194.933914
	weight to h = -283.358756
	weight to y = -189.532591
}
*/
void entry()
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

    printNetwork(h, z, &data);
    learnAverage(h, z, &data, 2, 250);

    printNetwork(h, z, &data);
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


    free(h->neurons);
    free(z->neurons);
    free(h);
    free(z);
}
