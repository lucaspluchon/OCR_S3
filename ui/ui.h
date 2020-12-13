#ifndef OCR_S3_UI_H
#define OCR_S3_UI_H
#include <gtk/gtk.h>
#include <../type/data.h>

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
