#include<stdio.h>

#ifndef BUILTINS_NEURAL_NETWORKS_H
#define BUILTINS_NEURAL_NETWORKS_H

////////////STRUCT
typedef struct Node Node;
struct Node
{
    double * activation;
    double *bias;
    size_t neuronsLen;
    double **neurons;
};
typedef struct NetworkData NetworkData;
struct NetworkData
{
    double excpect;
    double x;
    double y;
    double activations[2];
    double weights[5];
    double bias[2];
};


double sigmoideDerivate(double x) ;
double sigmoid(double x);
double randd();
void printRes(double res, double x, double y);
void printNode(Node *node, char name);
void printNetwork(Node *h, Node *z, NetworkData *data);
void updateTreeNode(Node *h, Node *z);
double updateNode(Node *node);

#endif
