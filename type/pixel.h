#ifndef PIXEL_H_INCLUDED
#define PIXEL_H_INCLUDED

typedef struct pixel pixel;
struct pixel
{
    int x;
    int y;
};

typedef struct PixelBlock PixelBlock;
struct PixelBlock
{
    pixel left_top;
    pixel right_top;
    pixel left_bottom;
    pixel right_bottom;
};

typedef struct array_size array_size;
struct array_size
{
    size_t nb_block;
    size_t nb_line;
    size_t nb_char;
};

#endif // PIXEL_H_INCLUDED
