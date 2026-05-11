#include <gtkmm.h>
#include <iostream>
#include <fstream>

class TextEditorUI : public Gtk::ApplicationWindow {
public:
    TextEditorUI() {
        set_title("Text Editor UI (gtkmm 4)");
        set_default_size(600, 400);

        vbox.set_orientation(Gtk::Orientation::VERTICAL);
        set_child(vbox);

        // --- Actions ---
        auto action_open = Gio::SimpleAction::create("open");
        action_open->signal_activate().connect([this](const Glib::VariantBase&) { openDoc(); });
        add_action(action_open);

        auto action_save = Gio::SimpleAction::create("save");
        action_save->signal_activate().connect([this](const Glib::VariantBase&) { saveDoc(); });
        add_action(action_save);

        auto action_exit = Gio::SimpleAction::create("exit");
        action_exit->signal_activate().connect([this](const Glib::VariantBase&) { close(); });
        add_action(action_exit);

        // --- Menu ---
        auto menu = Gio::Menu::create();
        auto file_menu = Gio::Menu::create();
        file_menu->append("Open", "win.open");
        file_menu->append("Save", "win.save");
        file_menu->append("Exit", "win.exit");
        menu->append_submenu("File", file_menu);

        menu_bar.set_menu_model(menu);
        vbox.append(menu_bar);

        // --- Scrolled Window & TextView ---
        scrolled.set_child(text_view);
        scrolled.set_expand(true);
        text_view.set_wrap_mode(Gtk::WrapMode::WORD);
        vbox.append(scrolled);
    }

private:
    Gtk::Box vbox;
    Gtk::PopoverMenuBar menu_bar;
    Gtk::ScrolledWindow scrolled;
    Gtk::TextView text_view;

    void openDoc() {
        auto dialog = Gtk::FileDialog::create();
        dialog->set_title("Выберите текстовый файл");

        auto filters = Gio::ListStore<Gtk::FileFilter>::create();
        auto filter_text = Gtk::FileFilter::create();
        filter_text->set_name("Текстовые файлы");
        filter_text->add_mime_type("text/plain");
        filters->append(filter_text);
        dialog->set_filters(filters);

        dialog->open(*this, sigc::bind(sigc::mem_fun(*this, &TextEditorUI::on_file_opened), dialog));
    }

    // Тот самый метод, которого не хватало
    void on_file_opened(const Glib::RefPtr<Gio::AsyncResult>& result, const Glib::RefPtr<Gtk::FileDialog>& dialog) {
        try {
            auto file = dialog->open_finish(result);
            std::ifstream inFile(file->get_path());
            if (inFile) {
                std::string content((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
                text_view.get_buffer()->set_text(content);
            }
        } catch (const Glib::Error& ex) {
            std::cerr << "Ошибка при открытии: " << ex.what() << std::endl;
        }
    }

    void saveDoc() {
        std::ofstream outFile("new_text_file.txt");
        if (!outFile.is_open()) {
            std::cerr << "File opening error" << std::endl;
            return;
        }

        auto buffer = text_view.get_buffer();
        // В GTK4 get_text() возвращает весь текст
        Glib::ustring text = buffer->get_text();
        outFile << text;
        outFile.close();
        std::cout << "Сохранено в new_text_file.txt" << std::endl;
    }
};

int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create("org.example.texteditor.ui");
    return app->make_window_and_run<TextEditorUI>(argc, argv);
}
