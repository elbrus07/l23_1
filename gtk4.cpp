#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_SIZE 100000

struct Data {
    GtkTextBuffer* buffer;
    GtkWidget* window;
    char* current_file;
};

void update_title(struct Data* data) {

    char title[512];
    if (data->current_file == NULL) {
        sprintf_s(title, sizeof(title), "new file");
    }
    else {
        sprintf_s(title, sizeof(title), "%s", data->current_file);
    }
    gtk_window_set_title(GTK_WINDOW(data->window), title);
}


int load_file(struct Data* data, const char* filename) {
    
    FILE* file = NULL;
    errno_t err = fopen_s(&file, filename, "r");
    if (err != 0 || file == NULL) return 0;

    char content[MAX_FILE_SIZE];
    size_t bytes_read = fread(content, 1, MAX_FILE_SIZE - 1, file);
    content[bytes_read] = '\0';
    fclose(file);

    gtk_text_buffer_set_text(data->buffer, content, -1);

    if (data->current_file) free(data->current_file);
    data->current_file = _strdup(filename);
    update_title(data);

    return 1;
}

int save_file(struct Data* data, const char* filename) {
    FILE* file = NULL;
    errno_t err = fopen_s(&file, filename, "w");
    if (err != 0 || file == NULL) return 0;

    GtkTextIter start, end;
    gtk_text_buffer_get_bounds(data->buffer, &start, &end);
    char* text = gtk_text_buffer_get_text(data->buffer, &start, &end, FALSE);

    fprintf(file, "%s", text);
    fclose(file);
    g_free(text);

    if (data->current_file) free(data->current_file);
    data->current_file = _strdup(filename);
    update_title(data);

    return 1;
}

void on_open_clicked(GtkWidget* button, gpointer user_data) {
    struct Data* data = (struct Data*)user_data;
    if (!load_file(data, "document.txt")) {
        g_print("Ошибка: не удалось открыть document.txt\n");
    }
}

void on_save_clicked(GtkWidget* button, gpointer user_data) {
    struct Data* data = (struct Data*)user_data;
    const char* filename = data->current_file ? data->current_file : "document.txt";
    if (!save_file(data, filename)) {
        g_print("Ошибка: не удалось сохранить \n", filename);
    }
}

void on_clear_clicked(GtkWidget* button, gpointer user_data) {
    struct Data* data = (struct Data*)user_data;
    gtk_text_buffer_set_text(data->buffer, "", -1);
}

void on_exit_clicked(GtkWidget* button, gpointer user_data) {
    struct Data* data = (struct Data*)user_data;
    gtk_window_close(GTK_WINDOW(data->window));
}

void on_color_clicked(GtkWidget* button, gpointer user_data) {
    struct Data* data = (struct Data*)user_data;

    const char* label = gtk_button_get_label(GTK_BUTTON(button));
    const char* color = "black";

    if (strcmp(label, "red") == 0) color = "red";
    else if (strcmp(label, "green") == 0) color = "green";
    else if (strcmp(label, "blue") == 0) color = "blue";

    GtkTextTag* tag = gtk_text_buffer_create_tag(data->buffer, NULL, NULL);
    g_object_set(tag, "foreground", color, NULL);

    GtkTextIter start, end;
    gtk_text_buffer_get_bounds(data->buffer, &start, &end);
    gtk_text_buffer_remove_all_tags(data->buffer, &start, &end);
    gtk_text_buffer_apply_tag(data->buffer, tag, &start, &end);
}

void on_size_clicked(GtkWidget* button, gpointer user_data) {
    struct Data* data = (struct Data*)user_data;

    const char* label = gtk_button_get_label(GTK_BUTTON(button));
    int size = 14;

    if (strcmp(label, "min") == 0) size = 12;
    else if (strcmp(label, "middle") == 0) size = 18;
    else if (strcmp(label, "big") == 0) size = 24;

    GtkTextTag* tag = gtk_text_buffer_create_tag(data->buffer, NULL, NULL);
    g_object_set(tag, "size-points", (double)size, NULL);

    GtkTextIter start, end;
    gtk_text_buffer_get_bounds(data->buffer, &start, &end);
    gtk_text_buffer_remove_all_tags(data->buffer, &start, &end);
    gtk_text_buffer_apply_tag(data->buffer, tag, &start, &end);
}

void activate(GtkApplication* app, gpointer user_data) {
    struct Data* data = (struct Data*)g_malloc(sizeof(struct Data));
    data->current_file = NULL;

    data->window = gtk_application_window_new(app);
    gtk_window_set_default_size(GTK_WINDOW(data->window), 800, 600);
    update_title(data);

    GtkWidget* vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_window_set_child(GTK_WINDOW(data->window), vbox);

    // Панель с кнопками
    GtkWidget* toolbar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_append(GTK_BOX(vbox), toolbar);

    GtkWidget* open_btn = gtk_button_new_with_label("open");
    GtkWidget* save_btn = gtk_button_new_with_label("save");
    GtkWidget* clear_btn = gtk_button_new_with_label("clean");
    GtkWidget* exit_btn = gtk_button_new_with_label("exit");

    gtk_box_append(GTK_BOX(toolbar), open_btn);
    gtk_box_append(GTK_BOX(toolbar), save_btn);
    gtk_box_append(GTK_BOX(toolbar), clear_btn);
    gtk_box_append(GTK_BOX(toolbar), exit_btn);

    // Панель с цветами
    GtkWidget* color_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_append(GTK_BOX(vbox), color_box);

    GtkWidget* red_btn = gtk_button_new_with_label("red");
    GtkWidget* green_btn = gtk_button_new_with_label("green");
    GtkWidget* blue_btn = gtk_button_new_with_label("blue");

    gtk_box_append(GTK_BOX(color_box), red_btn);
    gtk_box_append(GTK_BOX(color_box), green_btn);
    gtk_box_append(GTK_BOX(color_box), blue_btn);


    GtkWidget* size_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_append(GTK_BOX(vbox), size_box);

    GtkWidget* small_btn = gtk_button_new_with_label("min");
    GtkWidget* medium_btn = gtk_button_new_with_label("middle");
    GtkWidget* large_btn = gtk_button_new_with_label("big");

    gtk_box_append(GTK_BOX(size_box), small_btn);
    gtk_box_append(GTK_BOX(size_box), medium_btn);
    gtk_box_append(GTK_BOX(size_box), large_btn);

    GtkWidget* scrolled = gtk_scrolled_window_new();
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled),
        GTK_POLICY_AUTOMATIC,
        GTK_POLICY_AUTOMATIC);

    gtk_widget_set_hexpand(scrolled, TRUE);
    gtk_widget_set_vexpand(scrolled, TRUE);

    gtk_box_append(GTK_BOX(vbox), scrolled);

    GtkWidget* text_view = gtk_text_view_new();
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled), text_view);

    data->buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));

    g_signal_connect(open_btn, "clicked", G_CALLBACK(on_open_clicked), data);
    g_signal_connect(save_btn, "clicked", G_CALLBACK(on_save_clicked), data);
    g_signal_connect(clear_btn, "clicked", G_CALLBACK(on_clear_clicked), data);
    g_signal_connect(exit_btn, "clicked", G_CALLBACK(on_exit_clicked), data);

    g_signal_connect(red_btn, "clicked", G_CALLBACK(on_color_clicked), data);
    g_signal_connect(green_btn, "clicked", G_CALLBACK(on_color_clicked), data);
    g_signal_connect(blue_btn, "clicked", G_CALLBACK(on_color_clicked), data);

    g_signal_connect(small_btn, "clicked", G_CALLBACK(on_size_clicked), data);
    g_signal_connect(medium_btn, "clicked", G_CALLBACK(on_size_clicked), data);
    g_signal_connect(large_btn, "clicked", G_CALLBACK(on_size_clicked), data);

    gtk_window_present(GTK_WINDOW(data->window));
}

int main(int argc, char* argv[]) {
    GtkApplication* app = gtk_application_new("org.example.editor", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}