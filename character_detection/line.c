#include "headers/segmentation.h"


void detect_line(ocr_data* data, pixel_block block, array_pos pos)
{
    bool detected_black = false;
    bool inDetection = false;
    int c = 0;
    pixel_block block_temp = block;

    for (int y = block.left_top.y; y <= block.left_bottom.y; y++)
    {
        detected_black = false;
        for (int x = block.left_top.x; x <= block.right_top.x; x++)
        {
            c = Pixel_GetR(SDL_GetPixel32(data->sdl.image,x,y));
            if (c == 0)
            {
                detected_black = true;
                break;
            }
        }

        if (detected_black)
        {
            if (inDetection == false)
            {
                block_temp.left_top.y = y;
                block_temp.right_top.y = y;
            }
            inDetection = true;
        }

        if ((detected_black == false || y == data->sdl.image->h - 1) && inDetection)
        {
            inDetection = false;
            block_temp.left_bottom.y = y;
            block_temp.right_bottom.y = y;
            if (pos.line >= data->text_array->blocks[pos.block].nb_line)
            {
                line_add(&data->text_array->blocks[pos.block]);
            }
            data->text_array->blocks[pos.block].lines[pos.line].top_y = block_temp.left_top.y;
            data->text_array->blocks[pos.block].lines[pos.line].bottom_y = block_temp.left_bottom.y;
            detect_char_vertical(data,block_temp,pos);
            pos.line++;
        }
    }

}