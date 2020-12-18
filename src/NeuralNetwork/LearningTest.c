#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "../type/pixel.h"
#include "../image_preprocessing/headers/preprocessing.h"
#include "../character_detection/headers/segmentation.h"
#include "headers/read.h"
#include "headers/NeuralNetworkTools.h"
#include "headers/ForwardProp.h"
#include <string.h>


int testOnLetter(NeuralNetwork* network, int letter, int randPolice)
{
    char filename[] = "data/letters/000/00.png";

    char dirNum[25];
    sprintf(dirNum, "%i", letter);

    //int randPolice = (int)((randd() + 1 ) * 7 / 2);
    //int randPolice = 0;
    char fileNum[25];
    sprintf(fileNum, "%i", randPolice);

    if (letter < 100)
    {
        filename[14] = dirNum[0];
        filename[15] = dirNum[1];
    }
    else
    {
        filename[13] = dirNum[0];
        filename[14] = dirNum[1];
        filename[15] = dirNum[2];
    }

    if (randPolice < 10)
    {
        filename[18] = fileNum[0];
    }
    else
    {
        filename[17] = fileNum[0];
        filename[18] = fileNum[1];
    }



    ocr_data data = apply_segmentation_for_training(filename);
    struct text* text = data.text_array;
    SDL_Surface* image = data.sdl.image;



    pixel_block caractere = text->blocks[0].lines[0].chrs[0];

    int* chr_image = get_pixel_block(image, caractere.left_top.x, caractere.left_top.y,
                                     caractere.right_bottom.x, caractere.right_bottom.y);

    int* chr_resized = resize(chr_image, caractere.right_bottom.x - caractere.left_top.x,
                              caractere.right_bottom.y - caractere.left_top.y);
    //test_sdl_neural(chr_resized, Neural_Network_Entry_Size, Neural_Network_Entry_Size);
    for (size_t i = 0; i < network->inputNumber; i++)
    {
        network->activations->data[i] = chr_resized[i];
    }

    forwardProp(network);

    double *output = &(network->activations->data[network->inputNumber + network->hidenNumber]);
    size_t maxI = 0;
    for (size_t i = 0; i < network->outputNumber; i++)
    {
        if (output[i] > output[maxI])
        {
            maxI = i;
        }

    }
    char foundLetter;
    if (network->asciiOutputs->data[maxI] >= (int)('A') && network->asciiOutputs->data[maxI] <= (int)('Z'))
    {
        foundLetter = (char)(network->asciiOutputs->data[maxI] + (int)('a')  - (int)('A'));
    }
    else
    {
        foundLetter = (char)(network->asciiOutputs->data[maxI]);
    }
    
    int found = letter == foundLetter || letter == foundLetter - ((int)('a')  - (int)('A'));

    printf("%c - The network was given a %c and guessed it was a %c (police %i)", letter, letter, (char)((int)network->asciiOutputs->data[maxI]), randPolice);
    if (found)
    {
        printf("            (guessed right)");
    }

    printf("\nthe outputs were :");
    printList(output, network->outputNumber);
    printf("\n\n");
    free(chr_image);
    free(chr_resized);

    return found;

}

void testAllLetter(NeuralNetwork* network)
{
    printf("testOnAllLetter :\n\n");

    int founds = 0;

    for (size_t i = 0; i < network->outputNumber; i++)
    {
        for(int police = 0; police < Number_Police; police++)
        {
            founds += testOnLetter(network, (int)(network->asciiOutputs->data[i]), police);
        }
    }
    printf("\nHe guessed %i / %li right... Not bad !", founds, network->outputNumber * Number_Police);
}
