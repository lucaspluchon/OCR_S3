#ifndef OCR_S3_SEGMENTATION_H
#define OCR_S3_SEGMENTATION_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "../image_preprocessing/headers/preprocessing.h"
#include "../type/pixel.h"
#include "../type/data.h"
#include "../useful/builtin.h"

SDL_Surface* Detect_RLSA_Block(SDL_Surface* image, int n, ocr_data* data);


ocr_data apply_segmentation_for_training(char* path);
void apply_segmentation(ocr_data* data);
void detect_text(ocr_data* data);
void detect_verticalBlock(ocr_data* data, pixel_block block, bool detected_whitebefore, array_pos pos);
void detect_horizontalBlock(ocr_data* data, pixel_block block, bool detected_whitebefore, array_pos pos);
void detect_line(ocr_data* data, pixel_block block, array_pos pos);
void detect_char_vertical(ocr_data* data, pixel_block block, array_pos pos);
void detect_char_horizontal(ocr_data* data, pixel_block block, array_pos pos);
double size_averageFont(text* arr);
void analyse_WrongLine(text_block* arr, double average_size, double average_space);
void char_draw(ocr_data* data);
double size_averageSpaceLine(text* arr);
double size_averageSpaceBlock(text* arr);
void analyse_WrongBlock(text* arr, double average_size, double average_space);



#endif //OCR_S3_SEGMENTATION_H
