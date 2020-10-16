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
void upadateTree(double *h[6], double *z[8]);
void learn(double x, double y, double activationH, double activationZ, double fWeight[3], double iWeight[2], double excpect, double *hb, double *hz, double res[7]);

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


    double *h[6] = {&activationH, &bh, &x, &iWeight[0], &y, &iWeight[1]};
    double *z[8] = {&activationZ, &bz, &x, &fWeight[0], &activationH, &fWeight[1], &y, &fWeight[2]};
    printf("Random synaptic weight : ");
    printNetworks(h, z);


    for (int i = 0; i < 1000; i++)
    {
        x = 1;
        y = 0;
        excpect = 1;
        upadateTree(h, z);
        double res1[7];
        learn(x, y, activationH, activationZ, fWeight, iWeight, excpect, &bh, &bz, res1);
        x = 1;
        y = 1;
        excpect = 0;
        upadateTree(h, z);
        double res2[7];
        learn(x, y, activationH, activationZ, fWeight, iWeight, excpect, &bh, &bz, res2);
        x = 0;
        y = 1;
        excpect = 1;
        upadateTree(h, z);
        double res3[7];
        learn(x, y, activationH, activationZ, fWeight, iWeight, excpect, &bh, &bz, res3);
        x = 0;
        y = 0;
        excpect = 0;
        upadateTree(h, z);
        double res4[7];
        learn(x, y, activationH, activationZ, fWeight, iWeight, excpect, &bh, &bz, res4);
        for (int i = 0; i < 3; i++)
        {
            fWeight[i] += res1[i] + res2[i] + res3[i] + res4[i];
        }
        for (int i = 0; i < 2; i++)
        {
            iWeight[i] += res1[i + 4] + res2[i + 4] + res3[i + 4] + res4[i + 4];
        }
        bh += res1[6] + res2[6] + res3[6] + res4[6];

        bz += res1[3] + res2[3] + res3[3] + res4[3];

    }


    printNetworks(h, z);
    x = 1;
    y = 1;
    upadateTree(h, z);
    printf("Res for 1, 1 = %f\n", activationZ);
    x = 0;
    y = 1;
    upadateTree(h, z);
    printf("Res for 0, 1 = %f\n", activationZ);
    x = 0;
    y = 0;
    upadateTree(h, z);
    printf("Res for 0, 0 = %f\n", activationZ);
    x = 1;
    y = 0;
    upadateTree(h, z);
    printf("Res for 1, 0 = %f\n", activationZ);
}

double delta(double error, double out)
{
    double v = 2;
    return error * out * v;
}

// double deltaHiden(double out, double outi, double dk, double w)
// {
//     double v = 1;
//     double d = sigmoideDerivate(out) * dk * w;
//     return v * d * outi;
// }


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

void learn(double x, double y, double activationH, double activationZ, double fWeight[3], double iWeight[2], double excpect, double *hb, double *hz, double res[7])
{
    //#3
    double error = (excpect - activationZ) * sigmoideDerivate(activationZ);
    double hError = sigmoideDerivate(activationH) * error * fWeight[1];

    //#4
    // double deltaF0 = delta(error, x);
    // double deltaF1 = delta(error, activationH);
    // double deltaF2 = delta(error, y);

    res[0] = delta(error, x);
    res[1] = delta(error, activationH);
    res[2] = delta(error, y);
    // double deltaBH = deltaHiden(1, activationZ, error, hz);

    res[3] = delta(error, 1);

    res[4] = delta(hError, x);
    res[5] = delta(hError, y);
    res[6] = delta(hError, 1);


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


