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
  return (double)rand() / (RAND_MAX + 1.0);
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