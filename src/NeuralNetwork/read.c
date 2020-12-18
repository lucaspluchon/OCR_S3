#include <stdio.h>
#include "../type/pixel.h"
#include <SDL2/SDL.h>
#include "../image_preprocessing/headers/preprocessing.h"
#include "headers/NeuralNetworkTools.h"
#include "headers/ForwardProp.h"
#include <err.h>
#include "../spell_checker/spell_checker.h"


int* get_pixel_block(SDL_Surface* image, int x1, int y1, int x2, int y2)
{
    int width = x2 - x1;
    int height = y2 - y1;

    int* chr_image = malloc(width * height *sizeof(int));
    if(chr_image == NULL)
        errx(1, "Memory allocation failed get pixel");

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            int pixelColor = Pixel_GetR(SDL_GetPixel32(image, x1 + i, y1 + j));
            Uint32 pixel = SDL_GetPixel32(image, x1 + i, y1 + j);
            if (pixelColor < 128) // cornercase idea : what if it's written white on black (block detection wouldn't work anyway)
            {
                chr_image[i * height + j] = 1;
            }
            else
            {
                chr_image[i * height + j] = 0;
            }
        }
    }
    //test_sdl_neural(chr_image, width, height);
    return chr_image;
}


int* resize(int* chr, int widthChr, int heightChr)
{
    int* chr_resized = malloc(Neural_Network_Entry_Size * Neural_Network_Entry_Size * sizeof(int));
    if(chr_resized == NULL)
        errx(1, "Memory allocation failed resize");

    //double newRatio = (double) ( widthChr > heightChr ? widthChr : heightChr ) / Neural_Network_Entry_Size;
    double newRatioX = (double) (widthChr) / Neural_Network_Entry_Size;
    double newRatioY = (double) (heightChr) / Neural_Network_Entry_Size;
    

    for (int i = 0; i < Neural_Network_Entry_Size; i++)
    {
        for (int j = 0; j < Neural_Network_Entry_Size; j++)
        {
            int resX = i * newRatioX;
            int resY = j * newRatioY;

            if(resX >= widthChr || resY >= heightChr)
            {
                chr_resized[i * Neural_Network_Entry_Size + j] = 0;
            }
            else
            {
                chr_resized[i * Neural_Network_Entry_Size + j] = chr[resX * heightChr + resY];
            }
        }
    }
    //test_sdl_neural(chr_resized, Neural_Network_Entry_Size, Neural_Network_Entry_Size);
    return chr_resized;
}

char readLetter(NeuralNetwork* network, pixel_block caractere, SDL_Surface* image)
{
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
    //printList((&network->activations->data[network->inputNumber + network->hidenNumber]), network->outputNumber);

    double *output = &(network->activations->data[network->inputNumber + network->hidenNumber]);
    size_t maxI = 0;
    for (size_t i = 0; i < network->outputNumber; i++)
    {
        if (output[i] > output[maxI])
        {
            maxI = i;
        }
        
    }
    free(chr_image);
    free(chr_resized);

    if (network->asciiOutputs->data[maxI] >= (int)('A') && network->asciiOutputs->data[maxI] <= (int)('Z'))
    {
        return (char)((int)(network->asciiOutputs->data[maxI]) + (int)('a')  - (int)('A'));
    }
    
    return (char)(network->asciiOutputs->data[maxI]);
}

void fullRead(ocr_data* data)
{
    text* arr = data->text_array;
    SDL_Surface* image = data->sdl.image;
    NeuralNetwork* network = data->network;
    ocr_string* totalText = data->result;

    size_t lenFullText = 0;
    for (size_t i = 0; i < arr->nb_block; i++)
    {
        for (size_t j = 0; j < arr->blocks[i].nb_line; j++)
        {
            lenFullText += arr->blocks[i].lines[j].nb_char + 1;
        }
        lenFullText += 3;
    }


    for (size_t i = 0; i < arr->nb_block; i++)
    {
        for (size_t j = 0; j < arr->blocks[i].nb_line; j++)
        {
            int sumSpace = 0;
            for (size_t k = 0; k < arr->blocks[i].lines[j].nb_char - 1; k++)
            {
                pixel_block caractere = arr->blocks[i].lines[j].chrs[k];
                sumSpace += arr->blocks[i].lines[j].chrs[k + 1].left_top.x - caractere.right_top.x;
            }
            int averageSpace;
            if(arr->blocks[i].lines[j].nb_char == 1)
                averageSpace = 1;
            else
                averageSpace = sumSpace / (arr->blocks[i].lines[j].nb_char -1);


            char word[arr->blocks[i].lines[j].nb_char];
            int wordLen = 0;


            for (size_t k = 0; k < arr->blocks[i].lines[j].nb_char; k++)
            {
                pixel_block caractere = arr->blocks[i].lines[j].chrs[k];

                char c = readLetter(network, caractere, image);

                arr->blocks[i].lines[j].chrs[k].letter = c;

                word[wordLen] = c;
                wordLen++;
                
                if (k == arr->blocks[i].lines[j].nb_char - 1
                    || arr->blocks[i].lines[j].chrs[k + 1].left_top.x - caractere.right_top.x > averageSpace * 3 / 2)
                {
                    word[wordLen] = '\0';
                    char* wordCorrect;
                    if (data->spell_check)
                        wordCorrect = correct_word(word);
                    else
                        wordCorrect = word;
                    wordLen = 0;

                    for (size_t l = 0; l < strlen(wordCorrect); l++)
                    {
                        string_append(totalText, wordCorrect[l]);
                    }

                    string_append(totalText, ' ');

                    if (data->spell_check)
                        free(wordCorrect);
                }

            }
            if (j != arr->blocks[i].nb_line - 1)
                string_append(totalText, '\n');
        }
        if (i != arr->nb_block - 1)
        {
            string_append(totalText, '\n');
            string_append(totalText, '\n');
        }
    }
    string_append(totalText,'\0');
}



