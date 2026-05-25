#include <gtk/gtk.h>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

GtkWidget* textView;

void highlight_syntax()
{
    GtkTextBuffer* buffer =
        gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));

    GtkTextIter start, end;

    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);

    gtk_text_buffer_remove_all_tags(
        buffer,
        &start,
        &end
    );

    gchar* text =
        gtk_text_buffer_get_text(buffer, &start, &end, FALSE);

    string content = text;

    GtkTextTagTable* table =
        gtk_text_buffer_get_tag_table(buffer);

    GtkTextTag* blueTag =
        gtk_text_tag_table_lookup(table, "blue");

    GtkTextTag* greenTag =
        gtk_text_tag_table_lookup(table, "green");

    GtkTextTag* redTag =
        gtk_text_tag_table_lookup(table, "red");

    //подсветка int
    size_t pos = content.find("int");

    while (pos != string::npos)
    {
        GtkTextIter wordStart, wordEnd;

        gtk_text_buffer_get_iter_at_offset(
            buffer,
            &wordStart,
            pos
        );

        gtk_text_buffer_get_iter_at_offset(
            buffer,
            &wordEnd,
            pos + 3
        );

        gtk_text_buffer_apply_tag(
            buffer,
            blueTag,
            &wordStart,
            &wordEnd
        );

        pos = content.find("int", pos + 1);
    }

    //подвстветка return
    pos = content.find("return");

    while (pos != string::npos)
    {
        GtkTextIter wordStart, wordEnd;

        gtk_text_buffer_get_iter_at_offset(
            buffer,
            &wordStart,
            pos
        );

        gtk_text_buffer_get_iter_at_offset(
            buffer,
            &wordEnd,
            pos + 6
        );

        gtk_text_buffer_apply_tag(
            buffer,
            redTag,
            &wordStart,
            &wordEnd
        );

        pos = content.find("return", pos + 1);
    }

    //подвстветка if
    pos = content.find("if");

    while (pos != string::npos)
    {
        GtkTextIter wordStart, wordEnd;

        gtk_text_buffer_get_iter_at_offset(
            buffer,
            &wordStart,
            pos
        );

        gtk_text_buffer_get_iter_at_offset(
            buffer,
            &wordEnd,
            pos + 2
        );

        gtk_text_buffer_apply_tag(
            buffer,
            greenTag,
            &wordStart,
            &wordEnd
        );

        pos = content.find("if", pos + 1);
    }

    g_free(text);
}

//сохр.
void save_file(GtkWidget* widget, gpointer data)
{
    GtkTextBuffer* buffer =
        gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));

    GtkTextIter start, end;

    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);

    gchar* text =
        gtk_text_buffer_get_text(buffer, &start, &end, FALSE);

    ofstream file("note.txt");
    file << text;

    g_free(text);
}

//откр.
void open_file(GtkWidget* widget, gpointer data)
{
    ifstream file("note.txt");

    if (!file.is_open())
        return;

    stringstream buffer;
    buffer << file.rdbuf();

    GtkTextBuffer* textBuffer =
        gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));

    gtk_text_buffer_set_text(
        textBuffer,
        buffer.str().c_str(),
        -1
    );

    highlight_syntax();
}

//очистка
void clear_text(GtkWidget* widget, gpointer data)
{
    GtkTextBuffer* buffer =
        gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));

    gtk_text_buffer_set_text(buffer, "", -1);
}

int main(int argc, char* argv[])
{
    gtk_init(&argc, &argv);


    GtkWidget* window =
        gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title(
        GTK_WINDOW(window),
        "Mini Notepad"
    );

    gtk_window_set_default_size(
        GTK_WINDOW(window),
        1000,
        700
    );

    g_signal_connect(
        window,
        "destroy",
        G_CALLBACK(gtk_main_quit),
        NULL
    );

    //контейнер
    GtkWidget* vbox =
        gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    gtk_container_add(
        GTK_CONTAINER(window),
        vbox
    );

    // панелька
    GtkWidget* hbox =
        gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

    gtk_box_pack_start(
        GTK_BOX(vbox),
        hbox,
        FALSE,
        FALSE,
        5
    );

    //кнопка сохр
    GtkWidget* saveButton =
        gtk_button_new_with_label("Save");

    gtk_box_pack_start(
        GTK_BOX(hbox),
        saveButton,
        FALSE,
        FALSE,
        5
    );

    g_signal_connect(
        saveButton,
        "clicked",
        G_CALLBACK(save_file),
        NULL
    );

    //кнопка откр
    GtkWidget* openButton =
        gtk_button_new_with_label("Open");

    gtk_box_pack_start(
        GTK_BOX(hbox),
        openButton,
        FALSE,
        FALSE,
        5
    );

    g_signal_connect(
        openButton,
        "clicked",
        G_CALLBACK(open_file),
        NULL
    );

    //кнопка очистки
    GtkWidget* clearButton =
        gtk_button_new_with_label("Clear");

    gtk_box_pack_start(
        GTK_BOX(hbox),
        clearButton,
        FALSE,
        FALSE,
        5
    );

    g_signal_connect(
        clearButton,
        "clicked",
        G_CALLBACK(clear_text),
        NULL
    );

    //текст.поле
    textView = gtk_text_view_new();

    gtk_text_view_set_wrap_mode(
        GTK_TEXT_VIEW(textView),
        GTK_WRAP_WORD
    );

    //буфер 
    GtkTextBuffer* buffer =
        gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));

    // цвета 
    gtk_text_buffer_create_tag(
        buffer,
        "blue",
        "foreground",
        "blue",
        NULL
    );

    gtk_text_buffer_create_tag(
        buffer,
        "green",
        "foreground",
        "green",
        NULL
    );

    gtk_text_buffer_create_tag(
        buffer,
        "red",
        "foreground",
        "red",
        NULL
    );

    
    g_signal_connect(
        buffer,
        "changed",
        G_CALLBACK(+[](GtkTextBuffer*, gpointer)
        {
            highlight_syntax();
        }),
        NULL
    );

    //скролл
    GtkWidget* scroll =
        gtk_scrolled_window_new(NULL, NULL);

    gtk_container_add(
        GTK_CONTAINER(scroll),
        textView
    );

    gtk_box_pack_start(
        GTK_BOX(vbox),
        scroll,
        TRUE,
        TRUE,
        5
    );

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
