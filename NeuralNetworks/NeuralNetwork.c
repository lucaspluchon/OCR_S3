#include "include_ocr.h"
#include <math.h>


double sigmoideDerivate(double x) 
{
    return x * (1 - x);
}

double sigmoid(double x)
{
    return 1 / (1 + exp(-x));
}

double trueTable(double x, double y)
{
    if (x != 0 && x != 0){
        printf("error on x");
        return -1;
    }
    if (y != 0 && y != 0){
        printf("error on y");
        return -1;
    }
    double[2][2] table {
        0, 1
        1, 0

    return table[x][y];
    };
}

double randd() 
{
  return (double)rand() / (RAND_MAX + 1.0);
}

double dot(double a[2], double b[2])
{
    return a[0] * b[0] + a[1] * b[1];
}

void 

int main()
{


    double synaptciWeight[2] = {-0.5, -0.5};

    double traingInputs[4][2] = {
        {1, 1},
        {0, 1},
        {1, 0},
        {0, 0}
    };

    double trainingOutputs[4] = {0, 1, 1, 0};

    for (int i = 0; i < 1000; i++)
    {
        double inputLayer[4][2] = traingInputs;

        

        // double error = 

    }
    
    double a[2] = {1, 2};
    double b[2] = {2, 3};

    printf("")

}
