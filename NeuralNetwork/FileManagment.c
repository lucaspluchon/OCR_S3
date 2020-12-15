#include<stdio.h>
#include<stdlib.h>

#include"NeuralNetworkTools.h"


int writeData(NeuralNetwork* data)
{
    FILE *fp;
    fp = fopen("value", "w");
    if (fp != NULL)
    {
        fwrite(data->activations, sizeof(data->activations), 1, fp);
        fclose(fp);
        return 0;
    }
    return 1;
}


int readData(NeuralNetwork *data)
{
    FILE *fp;
    fp = fopen("value", "r");
    if (fp != NULL)
    {
        fread(data->activations, sizeof(data->activations), 1, fp);
        fclose(fp);
        return 0;
    }
    return 1;
}


int writeList(ListSet* l, char* name, char* listName)
{
    FILE *fp;
    fp = fopen(name, "w");
    if (fp != NULL)
    {
        fwrite(l, sizeof(ListSet), 1, fp);
        fclose(fp);
        FILE *fpl;
        fpl = fopen(listName, "w");
        if (fpl != NULL)
        {
            fwrite(l->data, sizeof(double) * l->size, 1, fpl);
            fclose(fpl);
            return 0;
        }
    }
    return 1;
}

int readList(ListSet* l, char* name, char* listName)
{
    FILE *fp;
    fp = fopen(name, "r");
    if (fp != NULL)
    {
        fread(l, sizeof(ListSet), 1, fp);
        fclose(fp);
        FILE* fpl;
        fpl = fopen(listName, "r");
        if (fpl != NULL)
        {
            fread(l->data, sizeof(double) * l->size, 1, fpl);
            fclose(fpl);
            return 0;
        }
    }
    return 1;
}
