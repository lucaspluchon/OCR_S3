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

void textArray_delete(text* txt)
{
    for (int i = 0; i < txt->nb_block; i++)
    {
        for (int j = 0; j < txt->blocks[i].nb_line; j++)
        {
            free(txt->blocks[i].lines[j].chrs);
            txt->blocks[i].lines[j].chrs = NULL;
            txt->blocks[i].lines[j].nb_char = 0;
            txt->blocks[i].lines[j].capacity = 0;
            txt->blocks[i].lines[j].bottom_y = 0;
            txt->blocks[i].lines[j].top_y = 0;
        }
        free(txt->blocks[i].lines);
        txt->blocks[i].lines = NULL;
        txt->blocks[i].nb_line = 0;
        txt->blocks[i].capacity = 0;
        txt->blocks[i].bottom_y = 0;
        txt->blocks[i].top_y = 0;
    }
    free(txt->blocks);
    txt->blocks = NULL;
    txt->blocks = 0;
    txt->capacity = 0;
    free(txt);
    txt = NULL;
}


void block_add(text* arr)
{
    arr->nb_block++;

    if (arr->nb_block > arr->capacity)
    {
        arr->capacity *= 2;
        text_block* tmp = realloc(arr->blocks,sizeof (text_block) * arr->capacity);
        if (tmp == NULL)
            errx(1,"Not enough memory to add a new block!");
        else
            arr->blocks = tmp;
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
        text_line* tmp = realloc(arr->lines,sizeof (text_line) * arr->capacity);
        if (tmp == NULL)
            errx(1,"Not enough memory to add a new line!");
        else
            arr->lines = tmp;

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
        pixel_block* tmp = realloc(arr->chrs,sizeof (pixel_block) * arr->capacity);
        if (tmp == NULL)
            errx(1,"Not enough memory to add a new char!");
        else
            arr->chrs = tmp;
    }
}

void chr_append(pixel_block x, size_t block, size_t line, text* text_array)
{
    if (line >= text_array->blocks[block].nb_line)
    {
        line_add(&text_array->blocks[block]);
    }

    chr_add(&text_array->blocks[block].lines[line]);
    size_t pos = text_array->blocks[block].lines[line].nb_char - 1;
    text_array->blocks[block].lines[line].chrs[pos] = x;
}


void chr_delete(text_line* arr, size_t pos)
{
    if (pos < arr->nb_char && pos >= 0)
    {
        arr->chrs[pos] = arr->chrs[pos + 1];
        for (size_t i = pos + 1; i < arr->nb_char - 1; i++)
        {
            arr->chrs[i] = arr->chrs[i + 1];
        }
        arr->nb_char--;
    }
}

void chr_merge_top(pixel_block* chr1, pixel_block* chr2)
{
    chr1->left_top.y = chr2->left_top.y;
    chr1->right_top.y = chr2->right_top.y;
}

void chr_merge_bottom(pixel_block* chr1, pixel_block* chr2)
{
    chr1->left_bottom.y = chr2->left_bottom.y;
    chr1->right_bottom.y = chr2->right_bottom.y;
}

