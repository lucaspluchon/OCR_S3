#include "../include_ocr.h"
#include <math.h>
#include"BuiltinsNeuralNetworks.h"
#include"BackPropagation.h"


void NeuraleNetwork() ;
double update(double *n[], int size);
void upadateTree(double *h[6], double *z[8]);


int main()
{
    NeuraleNetwork();
}

void NeuraleNetwork() 
{
    double excpect = 1;
    double x = 1;
    double y = 0;
    double iWeight[2] = {randd(), randd()};
    double fWeight[3] = {randd(), randd(), randd()};
    double activationH = 0;
    double bh = randd();
    double activationZ = 0;
    double bz = randd();


    double *h[6] = {&activationH, &bh, 
                    &x, &iWeight[0], 
                    &y, &iWeight[1]}
    ;
    double *z[8] = {&activationZ, &bz, 
                    &x, &fWeight[0], 
                    &activationH, &fWeight[1], 
                    &y, &fWeight[2]
    };
    printf("Random synaptic weight : ");
    printNetworks(h, z);


    for (int i = 0; i < 200 ; i++)
    {
        double res[7];
        double inputs[4][2] = {
            {1, 0},
            {1, 1},
            {0, 1},
            {0, 0}
        };
        double excpectTab[4] = {1, 0, 1, 0};

        double tempRes[7];
        for (int i = 0; i < 4; i++)
        {
            x = inputs[i][0];
            y = inputs[i][1];
            excpect = excpectTab[i];
            upadateTree(h, z);
            learn(x, y, activationH, activationZ, fWeight, iWeight, excpect, &bh, &bz, tempRes);
            for (int j = 0; j < 7; j++)
            {
                res[j] += tempRes[j];
            }
        }
        
        for (int i = 0; i < 3; i++)
        {
            fWeight[i] += res[i];
        }
        for (int i = 0; i < 2; i++)
        {
            iWeight[i] += res[i + 4];
        }
        bh += res[6];

        bz += res[3];

    }


    printNetworks(h, z);
    x = 1;
    y = 1;
    upadateTree(h, z);
    printRes(activationZ, x, y);
    x = 0;
    y = 1;
    upadateTree(h, z);
    printRes(activationZ, x, y);
    x = 0;
    y = 0;
    upadateTree(h, z);
    printRes(activationZ, x, y);
    x = 1;
    y = 0;
    upadateTree(h, z);
    printRes(activationZ, x, y);
}



double update(double *n[], int size)
{
    double res = *n[1];
    for (int i = 3; i < size; i += 2)
    {
        res += *n[i] * *n[i - 1];
    }
    return sigmoid(res);
}


void upadateTree(double *h[6], double *z[8])
{
    *h[0] = update(h, 6);
    *z[0] = update(z, 8);
}

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