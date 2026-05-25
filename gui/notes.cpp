#include <gtkmm.h>
#include <fstream>
#include <iostream>

class TextEditor : public Gtk::Window {
public:
    TextEditor() {
        set_title("GTKmm 4 Text Editor");
        set_default_size(600, 400);

        // Главный контейнер
        vbox.set_orientation(Gtk::Orientation::VERTICAL);
        set_child(vbox);

        // === Actions ===
        auto action_open = Gio::SimpleAction::create("open");
        action_open->signal_activate().connect(sigc::mem_fun(*this, &TextEditor::on_open));
        add_action(action_open);

        auto action_save = Gio::SimpleAction::create("save");
        action_save->signal_activate().connect(sigc::mem_fun(*this, &TextEditor::on_save));
        add_action(action_save);

        auto action_exit = Gio::SimpleAction::create("exit");
        action_exit->signal_activate().connect(sigc::mem_fun(*this, &TextEditor::on_exit));
        add_action(action_exit);

        // === Menu model ===
        auto menu = Gio::Menu::create();
        auto file_menu = Gio::Menu::create();

        file_menu->append("Open", "win.open");
        file_menu->append("Save", "win.save");
        file_menu->append("Exit", "win.exit");

        menu->append_submenu("File", file_menu);

        menu_bar.set_menu_model(menu);
        vbox.append(menu_bar);

        // === Text area ===
        scrolled.set_child(text_view);
        vbox.append(scrolled);
    }

private:
    Gtk::Box vbox;
    Gtk::PopoverMenuBar menu_bar;
    Gtk::ScrolledWindow scrolled;
    Gtk::TextView text_view;

    void on_open(const Glib::VariantBase&) {
        Gtk::FileChooserDialog dialog(*this, "Open File",
                                      Gtk::FileChooser::Action::OPEN);
        dialog.add_button("_Cancel", Gtk::ResponseType::CANCEL);
        dialog.add_button("_Open", Gtk::ResponseType::OK);

        if (dialog.run() == Gtk::ResponseType::OK) {
            std::ifstream file(dialog.get_file()->get_path());
            if (file) {
                std::string content((std::istreambuf_iterator<char>(file)),
                                     std::istreambuf_iterator<char>());
                text_view.get_buffer()->set_text(content);
            }
        }
    }

    void on_save(const Glib::VariantBase&) {
        Gtk::FileChooserDialog dialog(*this, "Save File",
                                      Gtk::FileChooser::Action::SAVE);
        dialog.add_button("_Cancel", Gtk::ResponseType::CANCEL);
        dialog.add_button("_Save", Gtk::ResponseType::OK);

        if (dialog.run() == Gtk::ResponseType::OK) {
            std::ofstream file(dialog.get_file()->get_path());
            if (file) {
                auto text = text_view.get_buffer()->get_text();
                file << text;
            }
        }
    }

    void on_exit(const Glib::VariantBase&) {
        close();
    }
};

int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create("org.example.texteditor");

    return app->make_window_and_run<TextEditor>(argc, argv);
}
