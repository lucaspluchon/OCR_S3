#include "../include_ocr.h"
#include <math.h>
#include"BuiltinsNeuralNetworks.h"

// Network dimension
#define INPUT_NUMBER = 2 
#define HIDEN_RAW_NUMBER = 1
#define OUTPUT_NUMEBR = 1

void NeuraleNetwork() ;
double update(double *n[], int size);
double delta(double error, double out);
double deltaHiden(double out, double outi, double dk, double w);
void upadateTree(double *h[6], double *z[8]);
void learn(double x, double y, double activationH, double activationZ, double fWeight[3], double iWeight[2], double excpect, double hb, double hz);

int main()
{
    NeuraleNetwork();
}

void NeuraleNetwork() 
{
    double excpect = 1;
    double x = 1;
    double y = 0;
    double iWeight[2] = {0.5, 0.5};
    double fWeight[3] = {0.5, 0.5, 0.5};
    double activationH = 0;
    double bh = 1;
    double activationZ = 0;
    double bz = 1;


    double *h[6] = {&activationH, &bh, &x, &iWeight[0], &y, &iWeight[1]};
    double *z[8] = {&activationZ, &bz, &x, &fWeight[0], &activationH, &fWeight[1], &y, &fWeight[2]};
    printf("Random synaptic weight : ");
    printNetworks(h, z);


    for (int i = 0; i < 10000; i++)
    {
        x = 1;
        y = 0;
        excpect = 1;
        upadateTree(h, z);
        learn(x, y, activationH, activationZ, fWeight, iWeight, excpect, bh, bz);
        x = 1;
        y = 1;
        excpect = 0;
        upadateTree(h, z);
        learn(x, y, activationH, activationZ, fWeight, iWeight, excpect, bh, bz);
        x = 0;
        y = 1;
        excpect = 1;
        upadateTree(h, z);
        learn(x, y, activationH, activationZ, fWeight, iWeight, excpect, bh, bz);
        x = 0;
        y = 0;
        excpect = 0;
        upadateTree(h, z);
        learn(x, y, activationH, activationZ, fWeight, iWeight, excpect, bh, bz);
    }


    printNetworks(h, z);
    upadateTree(h, z);
    printf("Res for 1, 1 = %f\n", activationZ);
    x = 0;
    upadateTree(h, z);
    printf("Res for 0, 1 = %f\n", activationZ);
    y = 0;
    upadateTree(h, z);
    printf("Res for 0, 0 = %f\n", activationZ);
    x = 1;
    upadateTree(h, z);
    printf("Res for 1, 0 = %f\n", activationZ);
}

double delta(double error, double out)
{
    double v = 1;
    return error * out * v;
}

double deltaHiden(double out, double outi, double dk, double w)
{
    double v = 1;
    double d = sigmoideDerivate(out) * dk * w;
    return v * d * outi;
}


double update(double *n[], int size)
{
    double res = *n[1];
    // size_t s = sizeof(n) / sizeof(n[0]);
    // printf("s = %zu\nn = %zu\nn0 = %zu\n", s, sizeof(n), sizeof(n[0]));
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

void learn(double x, double y, double activationH, double activationZ, double fWeight[3], double iWeight[2], double excpect, double hb, double hz)
{
//#3
    double error = (excpect - activationZ) * sigmoideDerivate(activationZ);

    //#4

    // double deltaF0 = delta(error, x);
    // double deltaF1 = delta(error, activationH);
    // double deltaF2 = delta(error, y);

    fWeight[0] += delta(error, x);
    fWeight[1] += delta(error, activationH);
    fWeight[2] += delta(error, y);
    // double deltaBH = deltaHiden(1, activationZ, error, hz);

    hz += deltaHiden(1, activationZ, error, hz);

    iWeight[0] += deltaHiden(activationH, x, error, iWeight[0]);
    iWeight[1] += deltaHiden(activationH, y, error, iWeight[1]);
    hb += deltaHiden(1, activationH, error, hb);

    // fWeight[0] += deltaF0;
    // fWeight[1] += deltaF1;
    // fWeight[2] += deltaF2;

    // hz += deltaBH;
}

//     NeuralNetworks();
// }


// void NeuralNetworks() 
// {
//     //Network dimension---
//     // int HIDEN_RAW_LENGTH[HIDEN_RAW_NUMBER] = {1}




//     double input[2] = {1, 0};
//     double toFirst[2] = {0, 0};
//     double toLast[3] = {0, 0, 0};
//     double h = 0;
//     double z = 0;
//     double hb = 0;
//     double zb = 0;

//     neth = updateActivationh(hb, input, toFirst);
//     h = sigmoid(neth)
//     netz = updateActivationz(zb, input, h, toLast);
//     z = sigmoid(netz)

//     printf("h = %f\nz = %f", h, z);

//     double error = (1 - z) * sigmoideDerivate(z);
// }



// double updateActivationh(double bias, double actviation[2], double weight[2])
// {
//     double res = bias;
//     for(int i = 0; i < 2; i++)
//     {
//         res += actviation[i] * weight[i];
//     }
    // return res;
// }

// double updateActivationz(double bias, double input[2], double activation, double weight[3])
// {
//     double res = bias;
//     res += input[0] * weight[0] + input[1] * weight[2] + activation * weight[1];
//     return res;
// }


