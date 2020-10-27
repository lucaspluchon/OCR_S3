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





void printNetworks(double *h[6], double *z[8])
{
    printf("Inputs : x = %f\ny = %f", *h[2], *h[4]);
    printf("\nh = {\n\tactivation = %f\n\tbias = %f\n\tweight to x = %f\n\tweight to y = %f\n}\n", *h[0], *h[1], *h[3], *h[5]);
    printf("\nz = {\n\tactivation = %f\n\tbias = %f\n\tweight to x = %f\n\tweight to h = %f\n\tweight to y = %f\n}\n", *z[0], *z[1], *z[3], *z[5], *z[7]);
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
    printf("    bias = %f\n", node->bias);
    for (size_t i = 0; i < node->neuronsLen; i += 2)
    {
        printf("    activation = %f", *(node->neurons[i]));
        printf("    weight = %f\n", *(node->neurons[i + 1]));
    }
}
