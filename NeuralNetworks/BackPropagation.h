#ifndef BACK_PROPAGATION_H
#define BACK_PROPAGATION_H

double delta(double error, double out);
void learn(double x, double y, double activationH, double activationZ, double fWeight[3], double iWeight[2], double excpect, double *hb, double *hz, double res[7]);

#endif