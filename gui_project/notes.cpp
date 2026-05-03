#include <gtkmm.h>
#include <fstream>
#include <iostream>

class TextEditor : public Gtk::Window {
public:
    TextEditor() {
        set_title("Simple GTKmm Text Editor");
        set_default_size(600, 400);

        // Layout
        vbox.set_orientation(Gtk::ORIENTATION_VERTICAL);
        add(vbox);

        // Menu
        auto item_file = Gtk::make_managed<Gtk::MenuItem>("File");
        menu_bar.append(*item_file);

        auto file_menu = Gtk::make_managed<Gtk::Menu>();
        item_file->set_submenu(*file_menu);

        auto item_open = Gtk::make_managed<Gtk::MenuItem>("Open");
        auto item_save = Gtk::make_managed<Gtk::MenuItem>("Save");
        auto item_exit = Gtk::make_managed<Gtk::MenuItem>("Exit");

        file_menu->append(*item_open);
        file_menu->append(*item_save);
        file_menu->append(*item_exit);

        item_open->signal_activate().connect(sigc::mem_fun(*this, &TextEditor::on_open));
        item_save->signal_activate().connect(sigc::mem_fun(*this, &TextEditor::on_save));
        item_exit->signal_activate().connect(sigc::mem_fun(*this, &TextEditor::on_exit));

        vbox.pack_start(menu_bar, Gtk::PACK_SHRINK);

        // Text area
        scroll.add(text_view);
        vbox.pack_start(scroll);

        show_all_children();
    }

private:
    Gtk::Box vbox;
    Gtk::MenuBar menu_bar;
    Gtk::ScrolledWindow scroll;
    Gtk::TextView text_view;

    void on_open() {
        Gtk::FileChooserDialog dialog(*this, "Open File", Gtk::FILE_CHOOSER_ACTION_OPEN);
        dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
        dialog.add_button("_Open", Gtk::RESPONSE_OK);

        if (dialog.run() == Gtk::RESPONSE_OK) {
            std::ifstream file(dialog.get_filename());
            if (file) {
                std::string content((std::istreambuf_iterator<char>(file)),
                                     std::istreambuf_iterator<char>());
                text_view.get_buffer()->set_text(content);
            }
        }
    }

    void on_save() {
        Gtk::FileChooserDialog dialog(*this, "Save File", Gtk::FILE_CHOOSER_ACTION_SAVE);
        dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
        dialog.add_button("_Save", Gtk::RESPONSE_OK);

        if (dialog.run() == Gtk::RESPONSE_OK) {
            std::ofstream file(dialog.get_filename());
            if (file) {
                auto text = text_view.get_buffer()->get_text();
                file << text;
            }
        }
    }

    void on_exit() {
        hide();
    }
};

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.example.texteditor");

    TextEditor editor;
    return app->run(editor);
}