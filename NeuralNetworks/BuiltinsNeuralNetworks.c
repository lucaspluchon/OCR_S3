#include <math.h>
#include<stdlib.h>
#include<stdio.h>

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

// double dot(double * a[], double * b[])
// {
//     size_t as = sizeof(a) / sizeof(a[0]);
//     size_t bs = sizeof(b) / sizeof(b[0]);

//     if (as != bs)
//     {
//         printf("dot dimension error");
//         return -1;
//     }

//     double res = 0;

//     for (int i = 0; i < as; i++)
//     {
//         res += a[i] * b[i];
//     }
//     return res;
// }

int lengthl(double l[])
{
    size_t s = sizeof(*l) / sizeof(l[0]);
    printf("%zu", sizeof(l[0]));
    printf("size %zu", s);
    return s;
}

void printNetworks(double *h[6], double *z[8])
{
    printf("Inputs : x = %f\ny = %f", *h[2], *h[4]);
    printf("\nh = {\n\tactivation = %f\n\tbias = %f\n\tweight to x = %f\n\tweight to y = %f\n}\n", *h[0], *h[1], *h[3], *h[5]);
    printf("\nz = {\n\tactivation = %f\n\tbias = %f\n\tweight to x = %f\n\tweight to h = %f\n\tweight to y = %f\n}\n", *z[0], *z[1], *z[3], *z[5], *z[7]);
}