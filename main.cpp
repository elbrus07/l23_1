#include <gtkmm.h>
#include <fstream>
#include <sstream>
#include <string>

class EditorWindow : public Gtk::Window {
public:
    EditorWindow() {
        set_title("Текстовый редактор");
        set_default_size(800, 500);

        main_box.set_orientation(Gtk::ORIENTATION_VERTICAL);
        add(main_box);

        // Верхняя панель кнопок
        toolbar_box.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
        toolbar_box.set_spacing(8);

        btn_new.set_label("Создать");
        btn_open.set_label("Открыть");
        btn_save.set_label("Сохранить");

        toolbar_box.pack_start(btn_new, Gtk::PACK_SHRINK);
        toolbar_box.pack_start(btn_open, Gtk::PACK_SHRINK);
        toolbar_box.pack_start(btn_save, Gtk::PACK_SHRINK);

        main_box.pack_start(toolbar_box, Gtk::PACK_SHRINK);

        // Текстовая область
        scrolled_window.add(text_view);
        scrolled_window.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
        main_box.pack_start(scrolled_window, Gtk::PACK_EXPAND_WIDGET);

        // Привязки кнопок к функциям
        btn_new.signal_clicked().connect(sigc::mem_fun(*this, &EditorWindow::on_new_clicked));
        btn_open.signal_clicked().connect(sigc::mem_fun(*this, &EditorWindow::on_open_clicked));
        btn_save.signal_clicked().connect(sigc::mem_fun(*this, &EditorWindow::on_save_clicked));

        show_all_children();
    }

private:
    Gtk::Box main_box;
    Gtk::Box toolbar_box;
    Gtk::Button btn_new, btn_open, btn_save;
    Gtk::ScrolledWindow scrolled_window;
    Gtk::TextView text_view;

    void on_new_clicked() {
        text_view.get_buffer()->set_text("");
    }

    void on_open_clicked() {
        Gtk::FileChooserDialog dialog(*this, "Открыть файл", Gtk::FILE_CHOOSER_ACTION_OPEN);
        dialog.add_button("Отмена", Gtk::RESPONSE_CANCEL);
        dialog.add_button("Открыть", Gtk::RESPONSE_OK);

        int result = dialog.run();
        if (result == Gtk::RESPONSE_OK) {
            std::string filename = dialog.get_filename();

            std::ifstream file(filename);
            if (!file.is_open()) {
                show_error("Не удалось открыть файл.");
                return;
            }

            std::stringstream buffer;
            buffer << file.rdbuf();
            text_view.get_buffer()->set_text(buffer.str());
        }
    }

    void on_save_clicked() {
        Gtk::FileChooserDialog dialog(*this, "Сохранить файл", Gtk::FILE_CHOOSER_ACTION_SAVE);
        dialog.add_button("Отмена", Gtk::RESPONSE_CANCEL);
        dialog.add_button("Сохранить", Gtk::RESPONSE_OK);
        dialog.set_do_overwrite_confirmation(true);

        int result = dialog.run();
        if (result == Gtk::RESPONSE_OK) {
            std::string filename = dialog.get_filename();

            std::ofstream file(filename);
            if (!file.is_open()) {
                show_error("Не удалось сохранить файл.");
                return;
            }

            std::string text = text_view.get_buffer()->get_text();
            file << text;
        }
    }

    void show_error(const std::string& message) {
        Gtk::MessageDialog dialog(*this, "Ошибка", false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK, true);
        dialog.set_secondary_text(message);
        dialog.run();
    }
};

int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.example.texteditor");
    EditorWindow window;
    return app->run(window);
}