#include "headers/segmentation.h"

/*
    -These function are useful to detect and correct the errors
    in segmentation
*/


double size_averageFont(text* arr)
{
    double total_size = 0;
    double nb_char = 0;

    for (size_t block = 0; block < arr->nb_block; block++)
    {
        for (size_t line = 0; line < arr->blocks[block].nb_line; line++)
        {
            nb_char += arr->blocks[block].lines[line].nb_char;
            for (size_t chr = 0; chr < arr->blocks[block].lines[line].nb_char; chr++)
            {
                total_size += arr->blocks[block].lines[line].chrs[chr].left_bottom.y -
                        arr->blocks[block].lines[line].chrs[chr].left_top.y;
            }
        }
    }
    return total_size / nb_char;
}

double size_averageSpaceLine(text* arr)
{
    double total_size = 0;
    double nb_space = 0;

    for (size_t i = 0; i < arr->nb_block; i++)
    {
        if (arr->blocks[i].nb_line > 0)
            nb_space += (double) arr->blocks[i].nb_line - 1;
        for (size_t j = 0; j < arr->blocks[i].nb_line - 1; j++)
        {
            total_size += arr->blocks[i].lines[j + 1].top_y - arr->blocks[i].lines[j].bottom_y;
        }
    }
    if (nb_space <= 1)
        return -1;
    return total_size / nb_space;
}

double size_averageSpaceBlock(text* arr)
{
    double total_size = 0;
    double nb_space = (double) arr->nb_block - 1;

    for (size_t i = 0; i < arr->nb_block - 1; i++)
    {
        total_size += arr->blocks[i + 1].top_y - arr->blocks[i].bottom_y;
    }

    if (nb_space <= 1)
        return -1;
    return total_size / nb_space;
}

//Detect wrong line (like "é" or "â") due to error of segmentation
void analyse_WrongLine(text_block* arr, double average_size, double average_space)
{
    double chr2_size;
    double space_size;
    pixel_block* chr1;
    pixel_block* chr2;
    size_t chr2_pos;


    for (size_t line = 0; line < arr->nb_line; line++)
    {
        if (line > 0)
        {
            chr2_pos = 0;
            space_size = arr->lines[line].top_y - arr->lines[line - 1].bottom_y;
            if (space_size < average_space / 1.5 || average_space == - 1)
            {
                for (size_t chr1_pos = 0; chr1_pos < arr->lines[line].nb_char && chr2_pos < arr->lines[line - 1].nb_char;
                chr1_pos++)
                {
                    chr1 = &arr->lines[line].chrs[chr1_pos];
                    chr2 = &arr->lines[line - 1].chrs[chr2_pos];

                    if (chr2->left_top.x >= chr1->left_top.x && chr2->right_top.x <= chr1->right_top.x)
                    {
                        chr2_size = chr2->left_bottom.y - chr2->left_top.y;
                        if (chr2_size < average_size)
                        {
                            chr_merge_top(chr1,chr2);
                            chr_delete(&arr->lines[line - 1],chr2_pos);
                            chr2_pos--;
                        }
                        chr2_pos++;
                    }
                }
            }
        }
        if (line < arr->nb_line - 1)
        {
            chr2_pos = 0;
            space_size = arr->lines[line + 1].top_y - arr->lines[line].bottom_y;
            if (space_size < average_space / 1.5 || average_space == - 1)
            {
                for (size_t chr1_pos = 0; chr1_pos < arr->lines[line].nb_char && chr2_pos < arr->lines[line + 1].nb_char;
                chr1_pos++)
                {
                    chr1 = &arr->lines[line].chrs[chr1_pos];
                    chr2 = &arr->lines[line + 1].chrs[chr2_pos];

                    if (chr2->left_top.x >= chr1->left_top.x && chr2->right_top.x <= chr1->right_top.x)
                    {
                        chr2_size = chr2->left_bottom.y - chr2->left_top.y;
                        if (chr2_size < average_size)
                        {
                            chr_merge_bottom(chr1,chr2);
                            chr_delete(&arr->lines[line + 1],chr2_pos);
                            chr2_pos--;
                        }
                        chr2_pos++;
                    }
                }
            }
        }
    }
}

//Detect wrong block (like "é" or "â") due to error of segmentation
void analyse_WrongBlock(text* arr, double average_size, double average_space)
{
    text_block* block1;
    text_block* block2;
    size_t chr2_pos;
    pixel_block* chr1;
    pixel_block* chr2;
    double chr2_size;
    double space_size;

    for (size_t block = 0; block < arr->nb_block; block++)
    {
        if (block > 0)
        {
            block1 = &arr->blocks[block];
            block2 = &arr->blocks[block - 1];
            space_size = block1->top_y - block2->bottom_y;

            if (block2->nb_line >= 1 && (space_size < average_space / 1.5 || average_space == - 1))
            {
                chr2_pos = 0;
                for (size_t chr1_pos = 0; chr1_pos < block1->lines[0].nb_char &&
                chr2_pos < block2->lines[block2->nb_line-1].nb_char; chr1_pos++)
                {
                    chr1 = &block1->lines[0].chrs[chr1_pos];
                    chr2 = &block2->lines[block2->nb_line - 1].chrs[chr2_pos];

                    if (chr2->left_top.x >= chr1->left_top.x && chr2->right_top.x <= chr1->right_top.x)
                    {
                        chr2_size = chr2->left_bottom.y - chr2->left_top.y;
                        if (chr2_size < average_size)
                        {
                            chr_merge_top(chr1,chr2);
                            chr_delete(&block2->lines[block2->nb_line - 1],chr2_pos);
                            chr2_pos--;
                        }
                        chr2_pos++;
                    }

                }
            }
        }
        if (block < arr->nb_block - 1)
        {
            block1 = &arr->blocks[block];
            block2 = &arr->blocks[block + 1];
            space_size = block2->top_y - block1->bottom_y;

            if (block2->nb_line >= 1 && (space_size < average_space / 1.5 || average_space == - 1))
            {
                chr2_pos = 0;
                for (size_t chr1_pos = 0; chr1_pos < block1->lines[block1->nb_line-1].nb_char &&
                                          chr2_pos < block2->lines[0].nb_char; chr1_pos++)
                {
                    chr1 = &block1->lines[block1->nb_line-1].chrs[chr1_pos];
                    chr2 = &block2->lines[0].chrs[chr2_pos];

                    if (chr2->left_top.x >= chr1->left_top.x && chr2->right_top.x <= chr1->right_top.x)
                    {
                        chr2_size = chr2->left_bottom.y - chr2->left_top.y;
                        if (chr2_size < average_size)
                        {
                            chr_merge_bottom(chr1,chr2);
                            chr_delete(&block2->lines[0],chr2_pos);
                            chr2_pos--;
                        }
                        chr2_pos++;
                    }

                }
            }
        }
    }
}
