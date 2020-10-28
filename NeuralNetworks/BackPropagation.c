#include"BuiltinsNeuralNetworks.h"


double delta(double error, double out, double v)
{
    return error * out * v;
}





void learnBackTree(Node *h, Node *z, NetworkData *data, double res[7], double v)
{
    double zError = (data->excpect - *(z->activation)) * sigmoideDerivate(*(z->activation));
    double hError = sigmoideDerivate(*(h->activation)) * zError * *(z->neurons[3]);


    // Second layer
    res[0] = delta(zError, *(z->neurons[0]), v);
    res[1] = delta(zError, *(z->neurons[2]), v);
    res[2] = delta(zError, *(z->neurons[4]), v);


    // First layer
    res[4] = delta(hError, *(h->neurons[0]), v);
    res[5] = delta(hError, *(h->neurons[2]), v);


    // Z bias
    res[3] = delta(zError, 1, v);
    // H bias
    res[6] = delta(hError, 1, v);
}


void learnAverage(Node *h, Node *z, NetworkData *data, double v, size_t iter)
{

    for (size_t i = 0; i < iter; i++)
    {
        double res[7];
        for(size_t k = 0; k < 7; k++)
        {
            res[k] = 0;
        }
        double inputs[4][2] = {
            {1, 0},
            {0, 0},
            {1, 1},
            {0, 1}
        };
        double excpectTab[4] = {1, 0, 0, 1};

        double tempRes[7];
        for (size_t k = 0; k < 7; k++)
        {
            tempRes[k] = 0;
        }
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

        for (size_t k = 0; k < 3; k++)
        {
            data->weights[k + 2] += res[k];
        }
        for (int k = 0; k < 2; k++)
        {
            data->weights[k] += res[k + 4];
        }
        *(h->bias) += res[6];

        *(z->bias) += res[3];

    }
}
