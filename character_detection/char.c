#include "headers/segmentation.h"

void detect_char(ocr_data* data, pixel_block block, array_pos pos)
{
    bool detected_black = false;
    bool inDetection = false;
    int c = 0;
    pixel_block block_temp = block;

    for (int x = block.left_top.x; x <= block.right_top.x; x++)
    {
        detected_black = false;
        for (int y = block.left_top.y; y <= block.left_bottom.y; y++)
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
                block_temp.left_top.x = x;
                block_temp.left_bottom.x = x;
                SDL_DrawLine(data->sdl.image_segmented, block_temp.left_top.x,block_temp.left_top.y,
                             block_temp.left_bottom.x,block_temp.left_bottom.y, 4278190335);
            }
            inDetection = true;
        }

        if ((detected_black == false || x == data->sdl.image->w - 1) && inDetection)
        {
            inDetection = false;
            block_temp.right_top.x = x;
            block_temp.right_bottom.x = x;
            SDL_DrawLine(data->sdl.image_segmented, block_temp.right_top.x,block_temp.right_top.y,
                         block_temp.right_bottom.x, block_temp.right_bottom.y, 4278190335);
            //chr_append(block_temp,pos.block,pos.line,data->text_array);
        }
    }
}

