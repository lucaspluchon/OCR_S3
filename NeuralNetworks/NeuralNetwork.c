#include<stdlib.h>
#include <math.h>
#include"BuiltinsNeuralNetworks.h"
#include"BackPropagation.h"


// void NeuraleNetwork() ;
// double update(double *n[], int size);
// void upadateTree(double *h[6], double *z[8]);
void entry();

int main()
{
    entry();
}

void entry()
{
    NetworkData data = 
    {
        .x = 40,
        .y = 41,
        .excpect = 1,
        .activations = {42, 43},
        .weights = {44, 45, 46, 47, 48}
    };

    Node *h;

    h = malloc(sizeof(*h));

    h->bias = randd();
    h->activation = &data.activations[0];
    h->neuronsLen = 4;

    h->neurons = malloc(sizeof(double *) * 4);
    
    h->neurons[0] = &data.x;
    h->neurons[1] = &data.weights[0];
    h->neurons[2] = &data.y;
    h->neurons[3] = &data.weights[1];

    Node *z;

    z = malloc(sizeof(*z));

    z->bias = randd();
    z->activation = &data.activations[1];
    z->neuronsLen = 6;

    z->neurons = malloc(sizeof(double *) * 6);

    z->neurons[0] = &data.x;
    z->neurons[1] = &data.weights[2];
    z->neurons[2] = &data.activations[1];
    z->neurons[3] = &data.weights[3];
    z->neurons[4] = &data.y;
    z->neurons[5] = &data.weights[4];

    printNode(h, 'h');
    printNode(z, 'z');
}

// void NeuraleNetwork() 
// {
//     double excpect = 1;
//     double x = 1;
//     double y = 0;
//     double iWeight[2] = {randd(), randd()};
//     double fWeight[3] = {randd(), randd(), randd()};
//     double activationH = 0;
//     double bh = randd();
//     double activationZ = 0;
//     double bz = randd();


//     double *h[6] = {&activationH, &bh, 
//                     &x, &iWeight[0], 
//                     &y, &iWeight[1]}
//     ;
//     double *z[8] = {&activationZ, &bz, 
//                     &x, &fWeight[0], 
//                     &activationH, &fWeight[1], 
//                     &y, &fWeight[2]
//     };
//     printf("Random synaptic weight : ");
//     printNetworks(h, z);


//     for (int i = 0; i < 200 ; i++)
//     {
//         double res[7];
//         double inputs[4][2] = {
//             {1, 0},
//             {1, 1},
//             {0, 1},
//             {0, 0}
//         };
//         double excpectTab[4] = {1, 0, 1, 0};

//         double tempRes[7];
//         for (int i = 0; i < 4; i++)
//         {
//             x = inputs[i][0];
//             y = inputs[i][1];
//             excpect = excpectTab[i];
//             upadateTree(h, z);
//             learn(x, y, activationH, activationZ, fWeight, iWeight, excpect, &bh, &bz, tempRes);
//             for (int j = 0; j < 7; j++)
//             {
//                 res[j] += tempRes[j];
//             }
//         }
        
//         for (int i = 0; i < 3; i++)
//         {
//             fWeight[i] += res[i];
//         }
//         for (int i = 0; i < 2; i++)
//         {
//             iWeight[i] += res[i + 4];
//         }
//         bh += res[6];

//         bz += res[3];

//     }


//     printNetworks(h, z);
//     x = 1;
//     y = 1;
//     upadateTree(h, z);
//     printRes(activationZ, x, y);
//     x = 0;
//     y = 1;
//     upadateTree(h, z);
//     printRes(activationZ, x, y);
//     x = 0;
//     y = 0;
//     upadateTree(h, z);
//     printRes(activationZ, x, y);
//     x = 1;
//     y = 0;
//     upadateTree(h, z);
//     printRes(activationZ, x, y);
// }



// double update(double *n[], int size)
// {
//     double res = *n[1];
//     for (int i = 3; i < size; i += 2)
//     {
//         res += *n[i] * *n[i - 1];
//     }
//     return sigmoid(res);
// }


// void upadateTree(double *h[6], double *z[8])
// {
//     *h[0] = update(h, 6);
//     *z[0] = update(z, 8);
// }

/* ###Good parametrs
Inputs : x = 0.000000
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
