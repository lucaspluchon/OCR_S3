#include "headers/segmentation.h"

void apply_segmentation(ocr_data* data)
{
    g_print("Segmentation started\n");
    data->sdl.image_rlsa = Detect_RLSA_Block(data->sdl.image,7);
    g_print("RLSA ended\n");
    data->text_array = textArray_new();
    detect_text(data);
    g_print("Segmentation ended\n");
}

void detect_text(ocr_data* data)
{

    SDL_Surface* image = data->sdl.image;

    pixel_block pblock = {{0,0},{image->w-1,0},{0,image->h-1},
                         {image->w-1,image->h-1}};
    array_pos pos = {0,0,0};

    data->sdl.image_segmented = Image_Copy(image);
    g_print("Detected block started\n");
    detect_verticalBlock(data, pblock, true, pos);
    g_print("Detected block ended\n");

    double average_size = size_averageFont(data->text_array);
    double average_spaceLine = size_averageSpaceLine(data->text_array);
    double average_spaceBlock = size_averageSpaceBlock(data->text_array);

    analyse_WrongBlock(data->text_array,average_size,average_spaceBlock);
    for (size_t block = 0; block < data->text_array->nb_block; block++)
    {
        analyse_WrongLine(&data->text_array->blocks[block], average_size, average_spaceLine);
    }

    char_draw(data);
}