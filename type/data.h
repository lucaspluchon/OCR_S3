#ifndef OCR_S3_DATA_H
#define OCR_S3_DATA_H
#include <gtk/gtk.h>
#include "pixel.h"

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
    GtkEntry* entry_threshold;
    GdkPixbuf* image_pixbuf;
    GtkEntry* entry_angle;
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

typedef struct ocr_data ocr_data;
struct ocr_data
{
    ui_data ui;
    sdl_data sdl;
    gchar* file_path;
    int no_destroy;
    text* text_array;
};

#endif //OCR_S3_DATA_H