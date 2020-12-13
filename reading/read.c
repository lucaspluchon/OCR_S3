#include <stdio.h>
#include "type/pixel.h"
#include <SDL2/SDL.h>

#define Neural_Network_Entry_Size 32


int** get_pixel_block(SDL_Surface* image, int x1, int y1, int x2, int y2)
{
    int width = x2 - x1;
    int height = y2 - y1;

    int** chr_image = malloc(width * sizeof(int));
    for (int i = 0; i < width; i++)
    {
        chr_image = malloc(height * sizeof(int));
    }

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            int pixelColor = Pixel_GetR(SDL_GetPixel32(image, x1 + i, y1 + j));
            if (pixelColor < 128) // cornercase idea : what if it's written white on black (block detection wouldn't work anyway)
            {
                chr_image[i][j] = 1;
            }
            else
            {
                chr_image[i][j] = 0;
            }
        }
    }

    return chr_image;
}


int** resize(int** chr, int widthChr, int heightChr)
{
    int** chr_resized = malloc(Neural_Network_Entry_Size * sizeof(int));
    for (int i = 0; i < Neural_Network_Entry_Size; i++)
    {
        chr_resized= malloc(Neural_Network_Entry_Size * sizeof(int));
    }

    double newRatio = (double) (max(widthChr, heightChr)) / Neural_Network_Entry_Size;

    for (int i = 0; i < Neural_Network_Entry_Size; i++)
    {
        for (int j = 0; j < Neural_Network_Entry_Size; j++)
        {
            int resX = i * newRatio;
            int resY = j * newRatio;

            if(resX >= widthChr || resY >= heightChr)
            {
                chr_resized[i][j] = 0;
            }
            else
            {
                chr_resized[i][j] = chr[resX][resY];
            }
        }
    }

    return chr;
}


void parcours(SDL_Surface* image, text* arr)
{
    for (int i = 0; i < arr->nb_block; i++)
    {
        for (int j = 0; j < arr->blocks[i].nb_line; j++)
        {
            int sumSpace = 0;
            for (int k = 0; k < arr->blocks[i].lines[j].nb_char; k++)
            {
                pixel_block caractere = arr->blocks[i].lines[j].chrs[k];
                if (k != arr->blocks[i].lines[j].nb_char - 1)
                {
                    sumSpace += arr->blocks[i].lines[j].chrs[k + 1].left_top.x - caractere.right_top.x;
                }
            }

            int averageSpace = sumSpace / arr->blocks[i].lines[j].nb_char;

            for (int k = 0; k < arr->blocks[i].lines[j].nb_char; k++)
            {
                pixel_block caractere = arr->blocks[i].lines[j].chrs[k];

                int** chr_image = get_pixel_block(image, caractere.left_top.x, caractere.left_top.y,
                    caractere.right_bottom.x, caractere.right_bottom.y);

                int** chr_resized = resize(chr_image, caractere.right_bottom.x - caractere.left_top.x,
                    caractere.right_bottom.y - caractere.left_top.y);

                // char c = networkSet(chr_resized)         send chr_resized to Neural network
                char c = '$';

                arr->blocks[i].lines[j].chrs[k].letter = c;

                printf("%c", c);
                
                if (k != arr->blocks[i].lines[j].nb_char - 1 
                    && arr->blocks[i].lines[j].chrs[k + 1].left_top.x - caractere.right_top.x > averageSpace * 4/3 )
                {
                    printf(" ");
                }
                
            }
            printf("\n");
        }
        printf("\n\n\n");
    }
}