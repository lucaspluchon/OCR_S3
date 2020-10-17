#include<stdio.h>
#include<stdlib.h>


void writeFile(double weight)
{
    FILE *fp;

    fp = fopen("value", "w");
    fprintf(fp, ((string) weight));

}

int main()
{
    double weight = -1.4523545;
    writeFile(weight);
}