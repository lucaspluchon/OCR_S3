#ifndef OCR_S3_UI_H
#define OCR_S3_UI_H
#include <gtk/gtk.h>

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
};

void on_image_choose(GtkFileChooserButton *widget, gpointer user_data);
void on_quitAnalyse(GtkFileChooserButton *widget, gpointer user_data);
void on_confirmAnalyse(GtkFileChooserButton *widget, gpointer user_data);
void on_copy(GtkFileChooserButton *widget, gpointer user_data);
void gtk_build_from_glade(GtkBuilder* builder, GError* error);
ocr_data init_data(GtkBuilder* builder);
void apply_sdl_on_gtk(ocr_data* data);
gboolean on_switch_auto (GtkSwitch *widget, gboolean state, gpointer user_data);
void on_threshold (GtkEntry *entry, gpointer  user_data);
void on_rotate(GtkEntry *entry, gpointer  user_data);

#endif //OCR_S3_UI_H
