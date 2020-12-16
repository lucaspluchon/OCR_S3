#include "headers/segmentation.h"
#include "../ui/ui.h"

text* apply_segmentation_for_training(char* path)
{
    ocr_data data =
            {
                    .ui = NULL,
                    .file_path = path,
                    .sdl = {
                            .threshold = -1,
                            .angle = -1,
                    },
                    .training = 1,
            };

    data.sdl.image_original = Image_Load(data.file_path);
    data.sdl.image = Image_Copy(data.sdl.image_original);
    Image_ApplyCorrection(&data);
    apply_segmentation(&data);

    return data.text_array;
}

void apply_segmentation(ocr_data* data)
{

    data->sdl.image_rlsa = Detect_RLSA_Block(data->sdl.image,7, data->ui.progress_main);
    //Progress_Set(data->ui.progress_main,0.6,data);
    data->text_array = textArray_new();
    detect_text(data);
}

void detect_text(ocr_data* data)
{

    SDL_Surface* image = data->sdl.image;

    pixel_block pblock = {{0,0},{image->w-1,0},{0,image->h-1},
                         {image->w-1,image->h-1}};
    array_pos pos = {0,0,0};

    data->sdl.image_segmented = Image_Copy(image);
    detect_verticalBlock(data, pblock, true, pos);

    //Progress_Set(data->ui.progress_main,0.8,data);

    double average_size = size_averageFont(data->text_array);
    double average_spaceLine = size_averageSpaceLine(data->text_array);
    double average_spaceBlock = size_averageSpaceBlock(data->text_array);

    analyse_WrongBlock(data->text_array,average_size,average_spaceBlock);
    for (size_t block = 0; block < data->text_array->nb_block; block++)
    {
        analyse_WrongLine(&data->text_array->blocks[block], average_size, average_spaceLine);
    }

    if (!data->training)
        char_draw(data);

    Progress_Set(data->ui.progress_main,1,data);
}
