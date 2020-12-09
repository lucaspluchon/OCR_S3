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
                SDL_DrawLine(data->sdl.image_segmented, block_temp.left_top.x,block_temp.left_top.y,
                             block_temp.right_top.x,block_temp.right_top.y, 4278255360);
            }
            inDetection = true;
        }

        if ((detected_black == false || y == data->sdl.image->h - 1) && inDetection)
        {
            inDetection = false;
            block_temp.left_bottom.y = y;
            block_temp.right_bottom.y = y;
            SDL_DrawLine(data->sdl.image_segmented, block_temp.left_bottom.x,block_temp.left_bottom.y,
                                   block_temp.right_bottom.x,block_temp.right_bottom.y, 4278255360);
            detect_char(data,block_temp,pos);
            pos.line++;
        }
    }

}