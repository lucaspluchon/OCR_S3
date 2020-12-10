#include <SDL2/SDL.h>
#include "ui.h"

// Main function.
int main (int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    gtk_init(NULL, NULL);

    GtkBuilder* builder = gtk_builder_new();
    GError* error = NULL;
    gtk_build_from_glade(builder,error);

    ocr_data data = init_data(builder);

    gtk_text_view_set_buffer(data.ui.text_result,data.ui.text_buffer);

    g_signal_connect(data.ui.window_main, "destroy", G_CALLBACK(gtk_main_quit),
                     &data);
    g_signal_connect(data.ui.window_image, "destroy", G_CALLBACK(gtk_main_quit),
                     &data);
    g_signal_connect(data.ui.window_result, "destroy", G_CALLBACK(gtk_main_quit),
                     &data);
    g_signal_connect(data.ui.button_imageChoose, "file-set", G_CALLBACK(on_image_choose),
                     &data);
    g_signal_connect(data.ui.button_quitAnalyse, "pressed", G_CALLBACK(on_quitAnalyse),
                     &data);
    g_signal_connect(data.ui.button_confirmAnalyse, "pressed", G_CALLBACK(on_confirmAnalyse),
                     &data);
    g_signal_connect(data.ui.button_copy, "pressed", G_CALLBACK(on_copy), &data);
    g_signal_connect(data.ui.switch_auto, "state-set", G_CALLBACK(on_switch_auto), &data);
    g_signal_connect(data.ui.entry_threshold, "activate", G_CALLBACK(on_threshold), &data);
    g_signal_connect(data.ui.entry_angle, "activate", G_CALLBACK(on_rotate), &data);

    // Runs the main loop.
    gtk_main();

    // Exits.
    return 0;
}