#ifndef OCR_S3_DATA_H
#define OCR_S3_DATA_H
#include <gtk/gtk.h>
#include "pixel.h"
#include "../NeuralNetwork/headers/NeuralNetworkTools.h"
#include <SDL2/SDL.h>

typedef struct ui_data ui_data;
struct ui_data
{
    GtkWindow* window_main;
    GtkWindow* window_image;
    GtkWindow* window_result;
    GtkFileChooserButton* button_imageChoose;
    GtkButton* button_confirmAnalyse;
    GtkButton* button_quitAnalyse;
    GtkButton* button_copy;
    GtkImage* image_viewer;
    GtkTextView* text_result;
    GtkTextBuffer* text_buffer;
    GtkClipboard* clipboard;
    GtkSwitch* switch_auto;
    GtkSwitch* switch_spell;
    GtkEntry* entry_threshold;
    GdkPixbuf* image_pixbuf;
    GtkEntry* entry_angle;
    GtkProgressBar* progress_main;
    GdkCursor* watch_cursor;
    GtkProgressBar* progress_neural;
    GtkButton* button_save;
    GtkFileFilter* filter1;
    GtkButton* button_again;
};

typedef struct sdl_data sdl_data;
struct sdl_data
{
    SDL_Surface* image;
    SDL_Surface* image_original;
    SDL_Surface* image_rlsa;
    SDL_Surface* image_segmented;
    int threshold;
    double angle;
};


typedef struct ocr_string ocr_string;
struct ocr_string
{
    char* string;
    size_t size;
    size_t capacity;
};

typedef struct ocr_data ocr_data;
struct ocr_data
{
    ui_data ui;
    sdl_data sdl;
    char* file_path;
    text* text_array;
    ocr_string* result;
    NeuralNetwork* network;
    int training;
    int spell_check;
};


void Data_delete(ocr_data* data);
void string_append(ocr_string* string_vector, char c);
void string_doubleCapacity(ocr_string* string_vector);
void string_free(ocr_string* string_vector);
ocr_string* string_new();

#endif //OCR_S3_DATA_H
