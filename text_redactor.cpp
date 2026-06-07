#include <gtk/gtk.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

GtkWidget* textView;
string activeColor = "red";

// Сканирует текст, удаляет старое форматирование и применяет тег выбранного цвета к ключевым словам
void highlight_syntax() {
    GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));
    GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    
    gtk_text_buffer_remove_all_tags(buffer, &start, &end);

    gchar* text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
    string content = text;
    g_free(text);

    GtkTextTagTable* table = gtk_text_buffer_get_tag_table(buffer);
    GtkTextTag* colorTag = gtk_text_tag_table_lookup(table, activeColor.c_str());

    vector<string> keywords = {"int", "return", "if", "else", "while"};

    for (const string& word : keywords) {
        size_t pos = content.find(word);
        while (pos != string::npos) {
            GtkTextIter wordStart, wordEnd;
            gtk_text_buffer_get_iter_at_offset(buffer, &wordStart, pos);
            gtk_text_buffer_get_iter_at_offset(buffer, &wordEnd, pos + word.length());
            gtk_text_buffer_apply_tag(buffer, colorTag, &wordStart, &wordEnd);
            pos = content.find(word, pos + 1);
        }
    }
}

// Записывает текущий текст из буфера в файл note.txt
void save_file() {
    GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));
    GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    gchar* text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
    
    ofstream file("note.txt");
    file << text;
    g_free(text);
}

// Считывает текст из файла note.txt и помещает его в буфер редактора
void open_file() {
    ifstream file("note.txt");
    if (!file.is_open()) return;
    
    stringstream buffer;
    buffer << file.rdbuf();
    GtkTextBuffer* textBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));
    gtk_text_buffer_set_text(textBuffer, buffer.str().c_str(), -1);
    highlight_syntax();
}

// Обработчик нажатия на кнопку "Save"
void on_save_clicked(GtkWidget* widget, gpointer data) { 
    save_file(); 
}

// Обработчик нажатия кнопки "Open"
void on_open_clicked(GtkWidget* widget, gpointer data) { 
    open_file(); 
}

// Очищает текстовое поле, сбрасывая содержимое буфера
void on_clear_clicked(GtkWidget* widget, gpointer data) {
    GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));
    gtk_text_buffer_set_text(buffer, "", -1);
}

// Устанавливает активный цвет подсветки и обновляет форматирование текста
void on_color_clicked(GtkWidget* widget, gpointer data) {
    activeColor = (char*)data;
    highlight_syntax();
}

// Обработчик события изменения текста, запускает пересчет подсветки
void on_text_changed(GtkTextBuffer* buffer, gpointer data) {
    highlight_syntax();
}

// Инициализирует GTK, создает элементы интерфейса и запускает главный цикл программы
int main(int argc, char* argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Mini Notepad");
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 700);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget* vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget* hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 5);

    // Кнопки управления файлами
    GtkWidget* saveBtn = gtk_button_new_with_label("Save");
    GtkWidget* openBtn = gtk_button_new_with_label("Open");
    GtkWidget* clearBtn = gtk_button_new_with_label("Clear");
    
    g_signal_connect(saveBtn, "clicked", G_CALLBACK(on_save_clicked), NULL);
    g_signal_connect(openBtn, "clicked", G_CALLBACK(on_open_clicked), NULL);
    g_signal_connect(clearBtn, "clicked", G_CALLBACK(on_clear_clicked), NULL);
    
    gtk_box_pack_start(GTK_BOX(hbox), saveBtn, FALSE, FALSE, 2);
    gtk_box_pack_start(GTK_BOX(hbox), openBtn, FALSE, FALSE, 2);
    gtk_box_pack_start(GTK_BOX(hbox), clearBtn, FALSE, FALSE, 2);
    gtk_box_pack_start(GTK_BOX(hbox), gtk_separator_new(GTK_ORIENTATION_VERTICAL), FALSE, FALSE, 5);

    // Кнопки выбора цвета
    const char* colors[] = {"red", "green", "orange", "yellow"};
    for (const char* col : colors) {
        GtkWidget* btn = gtk_button_new_with_label(col);
        g_signal_connect(btn, "clicked", G_CALLBACK(on_color_clicked), (gpointer)col);
        gtk_box_pack_start(GTK_BOX(hbox), btn, FALSE, FALSE, 2);
    }

    // Создание текстового поля и настройка тегов
    textView = gtk_text_view_new();
    GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));

    gtk_text_buffer_create_tag(buffer, "red", "foreground", "red", NULL);
    gtk_text_buffer_create_tag(buffer, "green", "foreground", "green", NULL);
    gtk_text_buffer_create_tag(buffer, "orange", "foreground", "#FFA500", NULL);
    gtk_text_buffer_create_tag(buffer, "yellow", "foreground", "yellow", NULL);

    g_signal_connect(buffer, "changed", G_CALLBACK(on_text_changed), NULL);

    GtkWidget* scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scroll), textView);
    gtk_box_pack_start(GTK_BOX(vbox), scroll, TRUE, TRUE, 5);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}