#include"BuiltinsNeuralNetworks.h"


double delta(double error, double out)
{
    double v = 1;
    return error * out * v;
}




// void learn(double x, double y, double activationH, double activationZ, double fWeight[3], double iWeight[2], double excpect, double *hb, double *hz, double res[7])
// {
//     //#3
//     double error = (excpect - activationZ) * sigmoideDerivate(activationZ);
//     double hError = sigmoideDerivate(activationH) * error * fWeight[1];

//     //#4

//     res[0] = delta(error, x);
//     res[1] = delta(error, activationH);
//     res[2] = delta(error, y);

//     res[3] = delta(error, 1);

//     res[4] = delta(hError, x);
//     res[5] = delta(hError, y);
//     res[6] = delta(hError, 1);
// }
