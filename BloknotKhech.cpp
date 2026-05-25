#include <gtk/gtk.h>
#include <pango/pango.h>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

GtkWidget* textView = nullptr;
string currentFilePath = "";
int fontSize = 14;
PangoFontDescription* fontDesc = nullptr;

void apply_font() {
    if (fontDesc) pango_font_description_free(fontDesc);
    fontDesc = pango_font_description_new();
    pango_font_description_set_family(fontDesc, "monospace");
    pango_font_description_set_size(fontDesc, fontSize * PANGO_SCALE);
    gtk_widget_override_font(textView, fontDesc);
}

void open_file(GtkWidget* widget, gpointer data) {
    GtkWidget* dialog = gtk_file_chooser_dialog_new("Открыть файл",
        GTK_WINDOW(data),
        GTK_FILE_CHOOSER_ACTION_OPEN,
        "_Отмена", GTK_RESPONSE_CANCEL,
        "_Открыть", GTK_RESPONSE_ACCEPT,
        NULL);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        char* filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        currentFilePath = filename;
        g_free(filename);

        ifstream file(currentFilePath);
        if (file.is_open()) {
            stringstream buffer;
            buffer << file.rdbuf();
            GtkTextBuffer* buf = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));
            gtk_text_buffer_set_text(buf, buffer.str().c_str(), -1);
        }
    }
    gtk_widget_destroy(dialog);
}

void save_file(GtkWidget* widget, gpointer data) {
    GtkWidget* dialog = gtk_file_chooser_dialog_new("Сохранить файл как",
        GTK_WINDOW(data),
        GTK_FILE_CHOOSER_ACTION_SAVE,
        "_Отмена", GTK_RESPONSE_CANCEL,
        "_Сохранить", GTK_RESPONSE_ACCEPT,
        NULL);

    gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(dialog), TRUE);
    if (!currentFilePath.empty()) {
        gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(dialog), currentFilePath.c_str());
    } else {
        gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(dialog), "untitled.txt");
    }

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        char* filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        currentFilePath = filename;
        g_free(filename);

        GtkTextBuffer* buf = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));
        GtkTextIter start, end;
        gtk_text_buffer_get_start_iter(buf, &start);
        gtk_text_buffer_get_end_iter(buf, &end);
        char* text = gtk_text_buffer_get_text(buf, &start, &end, FALSE);

        ofstream file(currentFilePath);
        if (file.is_open()) file << text;
        g_free(text);
    }
    gtk_widget_destroy(dialog);
}

void change_font(GtkWidget* widget, gpointer data) {
    int change = GPOINTER_TO_INT(data);
    fontSize += change;
    if (fontSize < 8) fontSize = 8;
    if (fontSize > 72) fontSize = 72;
    apply_font();
}

int main(int argc, char* argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Простой Редактор");
    gtk_window_set_default_size(GTK_WINDOW(window), 900, 600);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget* vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget* hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_halign(hbox, GTK_ALIGN_CENTER); // Центрируем панель
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 5);

    GtkWidget* btnOpen = gtk_button_new_with_label("Открыть");
    GtkWidget* btnSave = gtk_button_new_with_label("Сохранить как");
    GtkWidget* btnPlus  = gtk_button_new_with_label("Шрифт +");
    GtkWidget* btnMinus = gtk_button_new_with_label("Шрифт -");

    gtk_box_pack_start(GTK_BOX(hbox), btnOpen, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), btnSave, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), btnPlus, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), btnMinus, FALSE, FALSE, 0);

    g_signal_connect(btnOpen, "clicked", G_CALLBACK(open_file), window);
    g_signal_connect(btnSave, "clicked", G_CALLBACK(save_file), window);
    g_signal_connect(btnPlus, "clicked", G_CALLBACK(change_font), GINT_TO_POINTER(1));
    g_signal_connect(btnMinus, "clicked", G_CALLBACK(change_font), GINT_TO_POINTER(-1));

    GtkWidget* scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start(GTK_BOX(vbox), scroll, TRUE, TRUE, 0);

    textView = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(textView), GTK_WRAP_WORD_CHAR);
    gtk_container_add(GTK_CONTAINER(scroll), textView);

    apply_font();

    gtk_widget_show_all(window);
    gtk_main();

    if (fontDesc) pango_font_description_free(fontDesc);
    return 0;
}