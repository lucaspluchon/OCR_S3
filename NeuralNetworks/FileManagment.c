#include"BuiltinsNeuralNetworks.h"

#include<stdio.h>
#include<stdlib.h>




int writeData(NetworkData *data)
{
    FILE *fp;
    fp = fopen("value", "w");
    if (fp != NULL)
    {
        fwrite(data, sizeof(*data), 1, fp);
        fclose(fp);
        return 0;
    }
    return 1;
}


int readData(NetworkData *data)
{
    FILE *fp;
    fp = fopen("value", "r");
    if (fp != NULL)
    {
        fread(data, sizeof(*data), 1, fp);
        fclose(fp);
        return 0;
    }
    return 1;
}
