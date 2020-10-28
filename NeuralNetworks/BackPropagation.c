#include"BuiltinsNeuralNetworks.h"


double delta(double error, double out, double v)
{
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

void learnBackTree(Node *h, Node *z, NetworkData *data, double res[7], double v)
{
    double zError = (data->excpect - *(z->activation)) * sigmoideDerivate(*(z->activation));
    double hError = sigmoideDerivate(*(h->activation)) * zError * *(z->neurons[3]);


    // Second layer
    res[0] = delta(zError, *(z->neurons[0]), v);
    res[1] = delta(zError, *(z->neurons[2]), v);
    res[2] = delta(zError, *(z->neurons[4]), v);

    // Z bias
    res[3] = delta(zError, 1, v);

    // First layer
    res[4] = delta(hError, *(h->neurons[0]), v);
    res[5] = delta(hError, *(h->neurons[2]), v);


    // H bias
    res[6] = delta(hError, 1, v);
}


void learnAverage(Node *h, Node *z, NetworkData *data, double v, size_t iter)
{
    // printNode(z, 'z');
    for (size_t i = 0; i < iter; i++)
    {
        double res[7];
        for(size_t k = 0; k < 7; k++)
        {
            res[k] = 0;
        }
        double inputs[4][2] = {
            {1, 0},
            {1, 1},
            {0, 1},
            {0, 0}
        };
        double excpectTab[4] = {1, 0, 1, 0};

        double tempRes[7];
        for (size_t k = 0; k < 7; k++)
        {
            tempRes[k] = 0;
        }
        // printf("tremp res = %f\n", tempRes[2]);
        for (size_t k = 0; k < 4; k++)
        {
            data->x = inputs[k][0];
            data->y = inputs[k][1];
            data->excpect = excpectTab[k];
            updateTreeNode(h, z);
            learnBackTree(h, z, data, tempRes, v);
            for (int j = 0; j < 7; j++)
            {
                res[j] += tempRes[j];
            }
        }
        // printNode(z, 'z');
        // for (size_t j = 0; j < 7; j ++)
        // {
        //     printf("i = %f\n", res[j]);
        // }
        for (size_t k = 0; k < 3; k++)
        {
            // printNode(z, 'z');
            data->weights[k + 2] += res[k];
            // printNode(z, 'z');
        }
        // printNode(z, 'z');
        for (int k = 0; k < 2; k++)
        {
            data->weights[k] += res[k + 4];
        }
        // printNode(z, 'z');
        h->bias += res[6];
        // printNode(z, 'z');

        z->bias += res[3];
        // printNode(z, 'z');
        // data->weights[0] += res[4];
        // data->weights[1] += res[5];
        // data->weights[2] += res[0];
        // data->weights[3] += res[1];
        // data->weights[4] += res[2];

        // z->bias += res[3];
        // h->bias += res[6];
    }
}
