#include "headers/segmentation.h"

void detect_verticalBlock(ocr_data* data, pixel_block block, bool detected_whitebefore, array_pos pos)
{
    bool detected_black = false;
    bool detected_white = false;
    bool inDetection = false;
    int c = 0;
    pixel_block block_temp = block;

    for (int x = block.left_top.x; x <= block.right_top.x; x++)
    {
        detected_black = false;
        detected_white = false;
        for (int y = block.left_top.y; y <= block.left_bottom.y; y++)
        {
            c = Pixel_GetR(SDL_GetPixel32(data->sdl.image_rlsa,x,y));
            detected_black = detected_black || (c == 0);
            detected_white = detected_white && (c == 255);
        }
        if (detected_black)
        {
            if (inDetection == false)
            {
                block_temp.left_top.x = x;
                block_temp.left_bottom.x = x;
                SDL_DrawLine(data->sdl.image_segmented, block_temp.left_top.x,block_temp.left_top.y,
                                       block_temp.left_bottom.x,block_temp.left_bottom.y, 4294901760);
            }
            inDetection = true;
        }

        if ((detected_black == false || x == data->sdl.image->w - 1) && inDetection)
        {
            inDetection = false;
            block_temp.right_top.x = x;
            block_temp.right_bottom.x = x;
            SDL_DrawLine(data->sdl.image_segmented, block_temp.right_top.x,block_temp.right_top.y,
                         block_temp.right_bottom.x,block_temp.right_bottom.y, 4294901760);
            if (detected_white == true || detected_whitebefore == true)
                detect_horizontalBlock(data, block_temp, detected_white, pos);
            else
            {
                detect_line(data,block_temp,pos);
                pos.block++;
            }
        }
    }
}

void detect_horizontalBlock(ocr_data* data, pixel_block block, bool detected_whitebefore, array_pos pos)
{
    bool detected_black = false;
    bool detected_white = false;
    bool inDetection = false;
    int c = 0;
    pixel_block block_temp = block;
    for (int y = block.left_top.y; y <= block.left_bottom.y; y++)
    {
        detected_black = false;
        detected_white = false;
        for (int x = block.left_top.x; x <= block.right_top.x; x++)
        {
            c = Pixel_GetR(SDL_GetPixel32(data->sdl.image_rlsa,x,y));
            detected_black = detected_black || (c == 0);
            detected_white = detected_white && (c == 255);
        }

        if (detected_black)
        {
            if (inDetection == false)
            {
                block_temp.left_top.y = y;
                block_temp.right_top.y = y;
                SDL_DrawLine(data->sdl.image_segmented, block_temp.left_top.x,block_temp.left_top.y,
                             block_temp.right_top.x,block_temp.right_top.y, 4294901760);
            }
            inDetection = true;
        }

        if ((detected_black == false || y == data->sdl.image->h - 1) && inDetection)
        {
            inDetection = false;
            block_temp.left_bottom.y = y;
            block_temp.right_bottom.y = y;
            SDL_DrawLine(data->sdl.image_segmented, block_temp.left_bottom.x,block_temp.left_bottom.y,
                         block_temp.right_bottom.x,block_temp.right_bottom.y, 4294901760);

            if (detected_white == true || detected_whitebefore == true)
                detect_verticalBlock(data, block_temp, detected_white, pos);
            else
            {
                detect_line(data,block_temp,pos);
                pos.block++;
            }
        }
    }
}