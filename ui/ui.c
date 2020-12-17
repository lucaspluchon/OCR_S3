#include <SDL2/SDL.h>
#include "ui.h"
#include "err.h"
#include "../image_preprocessing/headers/preprocessing.h"
#include "../character_detection/headers/segmentation.h"

/*
    All the useful function for GTK and signal functions
*/


void Progress_Set(GtkProgressBar* progressBar, double value, ocr_data* data)
{
    if(data != NULL && progressBar != NULL && !data->training)
    {
        gtk_progress_bar_set_fraction(progressBar,value);
        while (g_main_context_iteration(NULL, FALSE));
    }
}

GdkPixbuf* pixbuf_from_sdl_at_scale(SDL_Surface* image_sdl,int w, int h)
{
    Uint32 src_format = image_sdl->format->format;
    Uint32 dst_format = SDL_PIXELFORMAT_RGBA32;
    double new_w,new_h;
    double ratio;
    GdkPixbuf *image_pixbuf = gdk_pixbuf_new (GDK_COLORSPACE_RGB, gtk_true(), 8,
                                        image_sdl->w, image_sdl->h);
    int rowstride = gdk_pixbuf_get_rowstride (image_pixbuf);
    guchar *pixels = gdk_pixbuf_get_pixels (image_pixbuf);

    SDL_LockSurface(image_sdl);
    SDL_ConvertPixels (image_sdl->w, image_sdl->h, src_format,
                       image_sdl->pixels, image_sdl->pitch,
                       dst_format, pixels, rowstride);
    SDL_UnlockSurface(image_sdl);

    if (image_sdl->w > w)
    {
        ratio = (double) w / image_sdl->w;
        new_w = image_sdl->w * ratio;
        new_h = image_sdl->h * ratio;
        GdkPixbuf* image_res = gdk_pixbuf_scale_simple(image_pixbuf,(int) new_w, (int) new_h,GDK_INTERP_BILINEAR);
        g_object_unref(image_pixbuf);
        return image_res;
    }
    else if (image_sdl->h > h)
    {
        ratio = (double) h / image_sdl->h;
        new_w = image_sdl->w * ratio;
        new_h = image_sdl->h * ratio;
        GdkPixbuf* image_res = gdk_pixbuf_scale_simple(image_pixbuf,(int) new_w, (int) new_h,GDK_INTERP_BILINEAR);
        g_object_unref(image_pixbuf);
        return image_res;
    }

   return image_pixbuf;
}


void apply_sdl_on_gtk(ocr_data* data)
{
    data->sdl.image = Image_Copy(data->sdl.image_original);
    Image_ApplyCorrection(data);
    g_print("Image correction ended\n");
    apply_segmentation(data);

    data->ui.image_pixbuf =  pixbuf_from_sdl_at_scale(data->sdl.image_segmented,742,600);
    gtk_image_set_from_pixbuf(data->ui.image_viewer,data->ui.image_pixbuf);
}

void on_image_choose(GtkFileChooserButton *widget, gpointer user_data)
{
    ocr_data* data = user_data;
    gtk_widget_set_visible(data->ui.progress_main, gtk_true());
    while (g_main_context_iteration(NULL, FALSE));
    gdk_window_set_cursor(gtk_widget_get_window(data->ui.window_main), data->ui.watch_cursor);
    data->file_path = gtk_file_chooser_get_filename((GtkFileChooser *) widget);
    if (data->file_path == NULL)
        errx(1,"Not enough memory");


    data->sdl.image_original = Image_Load(data->file_path);
    Progress_Set(data->ui.progress_main,0.1,data);

    g_print("Image loaded\n");

    gint x = 0;
    gint y = 0;
    gtk_window_get_position(data->ui.window_main,&x,&y);
    gtk_window_move(data->ui.window_image,x,y);

    apply_sdl_on_gtk(data);

    gtk_widget_show(data->ui.window_image);
    gtk_widget_hide(data->ui.window_main);
    gtk_widget_set_visible(data->ui.progress_main, gtk_false());
    Progress_Set(data->ui.progress_main,0,data);
    gdk_window_set_cursor(gtk_widget_get_window(data->ui.window_main), NULL);
}

void on_quitAnalyse(GtkFileChooserButton *widget, gpointer user_data)
{
    ocr_data* data = user_data;
    if (strcmp(data->file_path,"") != 0)
        g_free(data->file_path);
    data->file_path = "";
    gtk_widget_set_sensitive((GtkWidget *) data->ui.entry_threshold, FALSE);
    gtk_switch_set_active(data->ui.switch_auto,TRUE);
    gtk_entry_set_text(data->ui.entry_threshold, "");

    gint x = 0;
    gint y = 0;
    gtk_window_get_position(data->ui.window_image,&x,&y);
    gtk_window_move(data->ui.window_main,x,y);

    gtk_widget_show(data->ui.window_main);
    gtk_widget_hide(data->ui.window_image);
}

void on_confirmAnalyse(GtkFileChooserButton *widget, gpointer user_data)
{
    ocr_data* data = user_data;
    if (strcmp(data->file_path,"") != 0)
        g_free(data->file_path);
    data->file_path = "";

    gtk_widget_set_visible(data->ui.progress_neural, gtk_true());
    gdk_window_set_cursor(gtk_widget_get_window(data->ui.window_main), data->ui.watch_cursor);
    while (g_main_context_iteration(NULL, FALSE));

    gtk_text_buffer_set_text(data->ui.text_buffer,"HELLO WORLD !",-1);

    gint x = 0;
    gint y = 0;

    gtk_window_get_position(data->ui.window_image,&x,&y);
    gtk_window_move(data->ui.window_result,x,y);
    gtk_widget_show(data->ui.window_result);
    gtk_widget_hide(data->ui.window_image);

    gtk_widget_set_visible(data->ui.progress_neural, gtk_false());
    gdk_window_set_cursor(gtk_widget_get_window(data->ui.window_main), NULL);

}

void on_threshold(GtkEntry *entry, gpointer  user_data)
{
    ocr_data* data = user_data;
    data->sdl.threshold = (int) strtol(gtk_entry_get_text(entry),NULL,10);
    if (data->sdl.threshold  > 255)
        data->sdl.threshold  = 255;
    else if (data->sdl.threshold  < 0)
        data->sdl.threshold  = 0;
    apply_sdl_on_gtk(data);
}

void on_rotate(GtkEntry *entry, gpointer  user_data)
{
    ocr_data* data = user_data;
    data->sdl.angle = strtod(gtk_entry_get_text(entry),NULL);
    apply_sdl_on_gtk(data);
}

void on_copy(GtkFileChooserButton *widget, gpointer user_data)
{
    ocr_data* data = user_data;
    gtk_clipboard_set_text(data->ui.clipboard,"HELLO WORLD!",-1);
}

void on_save(GtkFileChooserButton *widget, gpointer user_data)
{
    ocr_data* data = user_data;
    GtkWidget* save_file_dialog = gtk_file_chooser_dialog_new ("Save File",
                                                               data->ui.window_result,
                                                               GTK_FILE_CHOOSER_ACTION_SAVE,
                                                               ("_Cancel"),
                                                               GTK_RESPONSE_CANCEL,
                                                               ("_Save"),
                                                               GTK_RESPONSE_ACCEPT,
                                                               NULL);
    GtkFileChooser* save_file_choose = GTK_FILE_CHOOSER(save_file_dialog);
    gint res = gtk_dialog_run (GTK_DIALOG (save_file_dialog));
    if (res == GTK_RESPONSE_ACCEPT)
    {
        char *path;
        path = gtk_file_chooser_get_filename(save_file_choose);
        if (data->file_path == NULL)
            errx(1,"Not enough memory");
        save_result(path,"Hello World !");
        g_free(path);
    }

    gtk_widget_destroy (save_file_dialog);
}

gboolean on_switch_auto(GtkSwitch *widget, gboolean state, gpointer user_data)
{
    ocr_data* data = user_data;
    if (state == gtk_true())
    {
        data->sdl.angle = -1;
        data->sdl.threshold = -1;
        apply_sdl_on_gtk(data);
    }
    gtk_widget_set_sensitive((GtkWidget *) data->ui.entry_threshold, !state);
    gtk_widget_set_sensitive((GtkWidget *) data->ui.entry_angle, !state);

    return FALSE;
}

gboolean on_switch_spell(GtkSwitch *widget, gboolean state, gpointer user_data)
{
    ocr_data* data = user_data;
    data->spell_check = (int) state;
    return FALSE;
}

void gtk_build_from_glade(GtkBuilder* builder, GError* error)
{
    if (gtk_builder_add_from_file(builder, "../ui_ocr.glade", &error) == 0)
    {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        gtk_main_quit();
    }
}

ocr_data init_data(GtkBuilder* builder)
{
    GtkWindow* window_main = GTK_WINDOW(gtk_builder_get_object(builder, "window_main"));
    GtkWindow* window_image = GTK_WINDOW(gtk_builder_get_object(builder, "window_image"));
    GtkWindow* window_result = GTK_WINDOW(gtk_builder_get_object(builder, "window_result"));
    GtkFileChooserButton* button_imageChoose = GTK_FILE_CHOOSER_BUTTON(gtk_builder_get_object(builder,"button_imagechoose"));
    GtkButton* button_confirmAnalyse = GTK_BUTTON(gtk_builder_get_object(builder, "button_confirmAnalyse"));
    GtkButton* button_quitAnalyse = GTK_BUTTON(gtk_builder_get_object(builder, "button_quitAnalyse"));
    GtkButton* button_copy = GTK_BUTTON(gtk_builder_get_object(builder, "button_copy"));
    GtkButton* button_save = GTK_BUTTON(gtk_builder_get_object(builder, "button_save"));
    GtkImage* image_viewer = GTK_IMAGE(gtk_builder_get_object(builder, "image_viewer"));
    GtkTextView* text_result = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "text_result"));
    GtkTextBuffer* text_buffer = GTK_TEXT_BUFFER(gtk_builder_get_object(builder, "text_buffer"));
    GtkClipboard* clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
    GtkSwitch * switch_auto = GTK_SWITCH(gtk_builder_get_object(builder, "switch_auto"));
    GtkEntry * entry_threshold = GTK_ENTRY(gtk_builder_get_object(builder, "entry_threshold"));
    GtkEntry * entry_angle = GTK_ENTRY(gtk_builder_get_object(builder, "entry_angle"));
    GtkProgressBar* progress_main = GTK_PROGRESS_BAR(gtk_builder_get_object(builder, "progress_main"));
    GtkProgressBar* progress_neural = GTK_PROGRESS_BAR(gtk_builder_get_object(builder, "progress_neural"));
    GtkSwitch* switch_spell = GTK_SWITCH(gtk_builder_get_object(builder, "switch_spell"));

    ocr_data data =
            {
                    .ui = {
                            .window_main = window_main,
                            .window_result = window_result,
                            .window_image = window_image,
                            .button_imageChoose = button_imageChoose,
                            .button_confirmAnalyse = button_confirmAnalyse,
                            .button_quitAnalyse = button_quitAnalyse,
                            .button_copy = button_copy,
                            .image_viewer = image_viewer,
                            .text_result = text_result,
                            .text_buffer = text_buffer,
                            .clipboard = clipboard,
                            .switch_auto = switch_auto,
                            .entry_threshold = entry_threshold,
                            .entry_angle = entry_angle,
                            .progress_main = progress_main,
                            .watch_cursor = gdk_cursor_new(GDK_WATCH),
                            .progress_neural = progress_neural,
                            .button_save = button_save,
                            .switch_spell = switch_spell,
                            .filter1 = gtk_file_filter_new(),
                        },
                    .file_path = "",
                    .sdl = {
                            .threshold = -1,
                            .angle = -1,
                    },
                    .training = 0,
                    .spell_check = 1,
            };

    gtk_file_filter_set_name(data.ui.filter1, "Images");
    gtk_file_filter_add_pattern(data.ui.filter1, "*.jpg");
    gtk_file_filter_add_pattern(data.ui.filter1, "*.png");
    gtk_file_filter_add_pattern(data.ui.filter1, "*.bmp");

    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(data.ui.button_imageChoose), data.ui.filter1);
    return data;
}
