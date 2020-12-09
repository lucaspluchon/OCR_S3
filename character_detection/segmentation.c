#include "headers/segmentation.h"

void apply_segmentation(ocr_data* data)
{
    data->sdl.image_rlsa = Detect_RLSA_Block(data->sdl.image,7);
    data->text_array = textArray_new();
    detect_text(data);
}

void detect_text(ocr_data* data)
{
    SDL_Surface* image = data->sdl.image;

    pixel_block block = {{0,0},{image->w-1,0},{0,image->h-1},
                         {image->w-1,image->h-1}};
    array_pos pos = {0,0,0};

    data->sdl.image_segmented = Image_Copy(image);
    detect_verticalBlock(data, block, true, pos);
}