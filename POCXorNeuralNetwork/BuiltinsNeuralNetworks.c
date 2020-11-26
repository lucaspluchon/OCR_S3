#include <math.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include"BuiltinsNeuralNetworks.h"

double sigmoideDerivate(double x) 
{
    return x * (1 - x);
}

double sigmoid(double x)
{
    return 1 / (1 + exp(-x));
}

double randd() 
{
    return (((double)rand() / (RAND_MAX)) * 2) - 1;
}





void printRes(double res, double x, double y)
{
    int cleanRes = 1;
    double percent = round(res * 10000) / 100;
    if (res < 0.5)
    {
        cleanRes = 0;
        percent = 100 - percent;
    }
    printf("Result for (%d, %d) : %d  (confidence %.2f%%)  %lf\n", (int)x, (int)y, cleanRes, percent, res);
}


void printNode(Node *node, char name)
{
    printf("Node %c\n", name);
    printf("    activation = %f\n", *(node->activation));
    printf("    bias = %f\n", *(node->bias));
    for (size_t i = 0; i < node->neuronsLen; i += 2)
    {
        printf("    activation = %f", *(node->neurons[i]));
        printf("    weight = %f\n", *(node->neurons[i + 1]));
    }
}

void printNetwork(Node *h, Node *z, NetworkData *data)
{
    printf("\n====neural network====\n");
    printf("x = %f\n", data->x);
    printf("y = %f\n", data->y);
    printf("excpect = %f\n", data->excpect);
    printf("Nodes : \n");
    printNode(h, 'h');
    printNode(z, 'z');
    printf("======\n");
}


double updateNode(Node *node)
{
    double res = *(node->bias);
    for(size_t i = 0; i < node->neuronsLen; i += 2)
    {
        res += *(node->neurons[i]) * *(node->neurons[i + 1]);
    }
    res = sigmoid(res);
    return res;
}

void updateTreeNode(Node *h, Node *z)
{
    *(h->activation) = updateNode(h);
    *(z->activation) = updateNode(z);
}
