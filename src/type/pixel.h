#ifndef PIXEL_H_INCLUDED
#define PIXEL_H_INCLUDED

typedef struct array_pos array_pos;
struct array_pos
{
    size_t block;
    size_t line;
    size_t chr;
};


typedef struct pixel pixel;
struct pixel
{
    int x;
    int y;
};

typedef struct pixel_block pixel_block;
struct pixel_block
{
    pixel left_top;
    pixel right_top;
    pixel left_bottom;
    pixel right_bottom;
    char letter;
};

typedef struct text_line text_line;
struct text_line
{
    size_t nb_char;
    size_t capacity;
    int top_y;
    int bottom_y;
    pixel_block* chrs;
};

typedef struct text_block text_block;
struct text_block
{
    size_t nb_line;
    size_t capacity;
    int top_y;
    int bottom_y;
    text_line* lines;
};

typedef struct text text;
struct text
{
    size_t nb_block;
    size_t capacity;
    text_block* blocks;
};

void chr_add(text_line * arr);
void line_add(text_block * arr);
void block_add(text* arr);
text* textArray_new();
void chr_append(pixel_block x, size_t block, size_t line, text* text_array);
void chr_delete(text_line* arr, size_t pos);
void chr_merge_top(pixel_block* chr1, pixel_block* chr2);
void chr_merge_bottom(pixel_block* chr1, pixel_block* chr2);
void textArray_delete(text* txt);
void line_delete(text_block* arr, size_t pos);
void block_delete(text* arr, size_t pos);
void check_line(text* txt);
void check_block(text* txt);


#endif // PIXEL_H_INCLUDED
