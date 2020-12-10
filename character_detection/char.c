#include "headers/segmentation.h"

void detect_char_vertical(ocr_data* data, pixel_block block, array_pos pos)
{
    bool detected_black = false;
    bool inDetection = false;
    int c;
    pixel_block block_temp = block;

    for (int x = block.left_top.x; x <= block.right_top.x; x++)
    {
        detected_black = false;
        for (int y = block.left_top.y; y <= block.left_bottom.y; y++)
        {
            c = Pixel_GetR(SDL_GetPixel32(data->sdl.image,x,y));
            if (!c)
            {
                detected_black = true;
                break;
            }
        }

        if (detected_black && !inDetection)
        {
            block_temp.left_top.x = x;
            block_temp.left_bottom.x = x;

            inDetection = true;
        }

        if ((detected_black == false || x == data->sdl.image->w - 1) && inDetection)
        {
            inDetection = false;
            block_temp.right_top.x = x;
            block_temp.right_bottom.x = x;
            detect_char_horizontal(data,block_temp,pos);
        }
    }
}

void detect_char_horizontal(ocr_data* data, pixel_block block, array_pos pos)
{
    bool detected_black = false;
    bool inDetection = false;
    int c;
    pixel_block block_temp = block;

    for (int y = block.left_top.y; y <= block.left_bottom.y; y++)
    {
        detected_black = false;
        for (int x = block.left_top.x; x <= block.right_top.x; x++)
        {
            c = Pixel_GetR(SDL_GetPixel32(data->sdl.image, x, y));
            if (!c)
            {
                detected_black = true;
                break;
            }
        }

        if (detected_black && inDetection)
        {
            block_temp.left_bottom.y = y;
            block_temp.right_bottom.y = y;
        }

        if (detected_black && !inDetection)
        {
            block_temp.left_top.y = y;
            block_temp.right_top.y = y;
            inDetection = true;
        }

    }

    SDL_DrawLine(data->sdl.image_segmented, block_temp.left_bottom.x, block_temp.left_bottom.y,
                 block_temp.right_bottom.x, block_temp.right_bottom.y, 4278190335);
    SDL_DrawLine(data->sdl.image_segmented, block_temp.right_top.x,block_temp.right_top.y,
                 block_temp.right_bottom.x, block_temp.right_bottom.y, 4278190335);
    SDL_DrawLine(data->sdl.image_segmented, block_temp.left_top.x,block_temp.left_top.y,
                 block_temp.left_bottom.x,block_temp.left_bottom.y, 4278190335);
    SDL_DrawLine(data->sdl.image_segmented, block_temp.left_top.x, block_temp.left_top.y,
                 block_temp.right_top.x, block_temp.right_top.y, 4278190335);
    chr_append(block_temp,pos.block,pos.line,data->text_array);
}

