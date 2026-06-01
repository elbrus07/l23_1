#include <gtk/gtk.h>
#include <pango/pango.h>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

GtkWidget* textView;

void highlight_syntax() {
    GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));
    GtkTextIter start, end;

    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);

    GtkTextTagTable* table = gtk_text_buffer_get_tag_table(buffer);
    GtkTextTag* blueTag = gtk_text_tag_table_lookup(table, "blue");
    GtkTextTag* greenTag = gtk_text_tag_table_lookup(table, "green");
    GtkTextTag* redTag = gtk_text_tag_table_lookup(table, "red");

    if (blueTag) gtk_text_buffer_remove_tag(buffer, blueTag, &start, &end);
    if (greenTag) gtk_text_buffer_remove_tag(buffer, greenTag, &start, &end);
    if (redTag) gtk_text_buffer_remove_tag(buffer, redTag, &start, &end);

    gchar* text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
    string content = text;

    auto apply_keyword_tag = [&](const string& keyword, GtkTextTag* tag) {
        size_t pos = content.find(keyword);
        while (pos != string::npos) {
            bool left_ok = (pos == 0 || !g_ascii_isalnum(content[pos - 1]));
            bool right_ok = (pos + keyword.length() == content.length() || !g_ascii_isalnum(content[pos + keyword.length()]));

            if (left_ok && right_ok && tag) {
                GtkTextIter wordStart, wordEnd;
                gtk_text_buffer_get_iter_at_offset(buffer, &wordStart, pos);
                gtk_text_buffer_get_iter_at_offset(buffer, &wordEnd, pos + keyword.length());
                gtk_text_buffer_apply_tag(buffer, tag, &wordStart, &wordEnd);
            }
            pos = content.find(keyword, pos + 1);
        }
    };

    apply_keyword_tag("int", blueTag);
    apply_keyword_tag("return", redTag);
    apply_keyword_tag("if", greenTag);

    g_free(text);
}

void create_file(GtkWidget* widget, gpointer data) {
    GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));
    gtk_text_buffer_set_text(buffer, "", -1);
}

void save_file(GtkWidget* widget, gpointer data) {
    GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));
    GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);

    gchar* text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
    ofstream file("note.txt");
    if (file.is_open()) {
        file << text;
    }
    g_free(text);
}

void open_file(GtkWidget* widget, gpointer data) {
    ifstream file("note.txt");
    if (!file.is_open()) return;

    stringstream buffer;
    buffer << file.rdbuf();

    GtkTextBuffer* textBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));
    
    // Временное отключение функции во избежание рекурсии
    g_signal_handlers_block_by_func(textBuffer, (gpointer)+[](GtkTextBuffer*, gpointer){}, NULL);
    
    gtk_text_buffer_set_text(textBuffer, buffer.str().c_str(), -1);
    highlight_syntax();
    
    g_signal_handlers_unblock_by_func(textBuffer, (gpointer)+[](GtkTextBuffer*, gpointer){}, NULL);
}

void apply_format_tag(const gchar* tag_name) {
    GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));
    GtkTextIter start, end;

    if (gtk_text_buffer_get_selection_bounds(buffer, &start, &end)) {
        GtkTextTagTable* table = gtk_text_buffer_get_tag_table(buffer);
        GtkTextTag* tag = gtk_text_tag_table_lookup(table, tag_name);

        if (tag) {
            if (gtk_text_iter_has_tag(&start, tag) && gtk_text_iter_has_tag(&end, tag)) {
                gtk_text_buffer_remove_tag(buffer, tag, &start, &end);
            } else {
                gtk_text_buffer_apply_tag(buffer, tag, &start, &end);
            }
        }
    }
}

void on_bold_clicked(GtkWidget* widget, gpointer data) { apply_format_tag("bold"); }
void on_italic_clicked(GtkWidget* widget, gpointer data) { apply_format_tag("italic"); }
void on_underline_clicked(GtkWidget* widget, gpointer data) { apply_format_tag("underline"); }

void on_app_activate(GtkApplication* app, gpointer user_data) {
    GtkWidget* window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Word & Code Editor (GTK 4)");
    gtk_window_set_default_size(GTK_WINDOW(window), 900, 600);

    GtkWidget* vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_window_set_child(GTK_WINDOW(window), vbox);

    GtkWidget* hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_append(GTK_BOX(vbox), hbox);

    GtkWidget* btnNew = gtk_button_new_with_label("Создать");
    GtkWidget* btnOpen = gtk_button_new_with_label("Открыть");
    GtkWidget* btnSave = gtk_button_new_with_label("Сохранить");
    
    GtkWidget* btnBold = gtk_button_new_with_label("Ж");
    GtkWidget* btnItalic = gtk_button_new_with_label("К");
    GtkWidget* btnUnderline = gtk_button_new_with_label("Ч");

    gtk_box_append(GTK_BOX(hbox), btnNew);
    gtk_box_append(GTK_BOX(hbox), btnOpen);
    gtk_box_append(GTK_BOX(hbox), btnSave);
    gtk_box_append(GTK_BOX(hbox), gtk_separator_new(GTK_ORIENTATION_VERTICAL));
    gtk_box_append(GTK_BOX(hbox), btnBold);
    gtk_box_append(GTK_BOX(hbox), btnItalic);
    gtk_box_append(GTK_BOX(hbox), btnUnderline);

    g_signal_connect(btnNew, "clicked", G_CALLBACK(create_file), NULL);
    g_signal_connect(btnOpen, "clicked", G_CALLBACK(open_file), NULL);
    g_signal_connect(btnSave, "clicked", G_CALLBACK(save_file), NULL);
    
    g_signal_connect(btnBold, "clicked", G_CALLBACK(on_bold_clicked), NULL);
    g_signal_connect(btnItalic, "clicked", G_CALLBACK(on_italic_clicked), NULL);
    g_signal_connect(btnUnderline, "clicked", G_CALLBACK(on_underline_clicked), NULL);

    textView = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(textView), GTK_WRAP_WORD);

    GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));

    gtk_text_buffer_create_tag(buffer, "blue", "foreground", "blue", NULL);
    gtk_text_buffer_create_tag(buffer, "green", "foreground", "darkgreen", NULL);
    gtk_text_buffer_create_tag(buffer, "red", "foreground", "red", NULL);

    gtk_text_buffer_create_tag(buffer, "bold", "weight", PANGO_WEIGHT_BOLD, NULL);
    gtk_text_buffer_create_tag(buffer, "italic", "style", PANGO_STYLE_ITALIC, NULL);
    gtk_text_buffer_create_tag(buffer, "underline", "underline", PANGO_UNDERLINE_SINGLE, NULL);

    g_signal_connect(buffer, "changed", G_CALLBACK(+[](GtkTextBuffer*, gpointer) { highlight_syntax(); }), NULL);

    GtkWidget* scroll = gtk_scrolled_window_new();
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scroll), textView);
    
    gtk_widget_set_vexpand(scroll, TRUE);
    gtk_box_append(GTK_BOX(vbox), scroll);

    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char* argv[]) {
    GtkApplication* app = gtk_application_new("org.gtk.example.wordeditor", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(on_app_activate), NULL);

    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
