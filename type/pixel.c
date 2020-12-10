#include <stdlib.h>
#include <err.h>
#include "pixel.h"

text* textArray_new()
{
    text* res = malloc(sizeof (text));

    if (res == NULL)
        errx(1,"Not create a text array");

    res->blocks = malloc(sizeof (text_block));
    res->nb_block = 0;
    res->capacity = 1;

    if (res->blocks == NULL)
        errx(1,"Not create a text array");

    res->blocks[0].lines = malloc(sizeof (text_line));
    res->blocks[0].nb_line = 0;
    res->blocks[0].capacity = 1;

    if (res->blocks[0].lines  == NULL)
        errx(1,"Not create a text array");

    res->blocks[0].lines[0].chrs = malloc(sizeof (pixel_block));
    res->blocks[0].lines[0].nb_char = 0;
    res->blocks[0].lines[0].capacity = 1;

    if (res->blocks[0].lines[0].chrs  == NULL)
        errx(1,"Not create a text array");

    return res;
}


void block_add(text* arr)
{
    arr->nb_block++;

    if (arr->nb_block > arr->capacity)
    {
        arr->capacity *= 2;
        arr->blocks = realloc(arr->blocks,sizeof (text_block) * arr->capacity);
        if (arr->blocks == NULL)
            errx(1,"Not enough memory to add a new block!");
    }

    if(arr->nb_block > 1)
    {
        arr->blocks[arr->nb_block - 1].lines = malloc(sizeof(text_line));
        arr->blocks[arr->nb_block - 1].capacity = 1;
        arr->blocks[arr->nb_block - 1].nb_line = 0;

        if (arr->blocks[arr->nb_block - 1].lines == NULL)
            errx(1, "Not enough memory to add a new block!");

        arr->blocks[arr->nb_block - 1].lines[0].chrs = malloc(sizeof(pixel_block));
        arr->blocks[arr->nb_block - 1].lines[0].capacity = 1;
        arr->blocks[arr->nb_block - 1].lines[0].nb_char = 0;

        if (arr->blocks[arr->nb_block - 1].lines[0].chrs == NULL)
            errx(1, "Not enough memory to add a new block!");
    }
}

void line_add(text_block * arr)
{
    arr->nb_line++;

    if (arr->nb_line > arr->capacity)
    {
        arr->capacity *= 2;
        arr->lines = realloc(arr->lines,sizeof (text_line) * arr->capacity);
        if (arr->lines == NULL)
            errx(1,"Not enough memory to add a new line!");
    }

    if (arr->nb_line > 1)
    {
        arr->lines[arr->nb_line - 1].chrs = malloc(sizeof(pixel_block));
        arr->lines[arr->nb_line - 1].capacity = 1;
        arr->lines[arr->nb_line - 1].nb_char = 0;

        if (arr->lines[arr->nb_line - 1].chrs == NULL)
            errx(1, "Not enough memory to add a new line!");
    }
}

void chr_add(text_line * arr)
{
    arr->nb_char++;
    if (arr->nb_char > arr->capacity)
    {
        arr->capacity *= 2;
        arr->chrs = realloc(arr->chrs,sizeof (pixel_block) * arr->capacity);
        if (arr->chrs == NULL)
            errx(1,"Not enough memory to add a new char!");
    }
}

void chr_append(pixel_block x, size_t block, size_t line, text* text_array)
{
    if (block >= text_array->nb_block)
    {
        block_add(text_array);
    }

    if (line >= text_array->blocks[block].nb_line)
    {
        line_add(&text_array->blocks[block]);
    }

    chr_add(&text_array->blocks[block].lines[line]);
    size_t pos = text_array->blocks[block].lines[line].nb_char - 1;
    text_array->blocks[block].lines[line].chrs[pos] = x;
}

