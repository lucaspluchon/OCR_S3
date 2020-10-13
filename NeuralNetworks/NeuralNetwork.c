#include "../include_ocr.h"
#include <math.h>
#include"BuiltinsNeuralNetworks.h"

// Network dimension
#define INPUT_NUMBER = 2 
#define HIDEN_RAW_NUMBER = 1
#define OUTPUT_NUMEBR = 1

void NeuraleNetwork() ;
double update(double *n[]);
double delta(double error, double out);

int main()
{
    NeuraleNetwork();
}

void NeuraleNetwork() 
{
    double excpect = 1;
    double x = 1;
    double y = 0;
    double iWeight[2] = {0, 0};
    double fWeight[3] = {0, 0, 0};
    double activationH = 0;
    double bh = 0;
    double activationZ = 0;
    double bz = 0;

    double *h[6] = {&activationH, &bh, &x, &iWeight[0], &y, &iWeight[1]};
    double *z[8] = {&activationZ, &bz, &x, &fWeight[0], &activationH, &fWeight[1], &y, &fWeight[2]};

    //Back prop

    //#2
    activationH = update(h);
    activationZ = update(z);
    printf("h = %f\nz = %f", activationH, activationZ);
    //#3
    double error = (excpect - activationZ) * sigmoideDerivate(activationZ);

    //#4
    fWeight[0] += delta(error, x);
    fWeight[1] += delta(error, activationH);
    fWeight[2] += delta(error, y);






}

double delta(double error, double out)
{
    double v = 0.1;
    return error * out * v;
}

double deltaHiden(double error, double out)
{
    return error * out * v;
}


double update(double *n[], double size)
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


