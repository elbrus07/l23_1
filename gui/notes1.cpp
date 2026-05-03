#include <gtkmm.h>

class TextEditorUI : public Gtk::ApplicationWindow {
public:
    TextEditorUI() {
        set_title("Text Editor UI (gtkmm 4)");
        set_default_size(600, 400);

        
        vbox.set_orientation(Gtk::Orientation::VERTICAL);
        set_child(vbox);

        
        auto action_open = Gio::SimpleAction::create("open");
        action_open->signal_activate().connect(
            [](const Glib::VariantBase&) {});
        add_action(action_open);

        auto action_save = Gio::SimpleAction::create("save");
        action_save->signal_activate().connect(
            [](const Glib::VariantBase&) {});
        add_action(action_save);

        auto action_exit = Gio::SimpleAction::create("exit");
        action_exit->signal_activate().connect(
            [this](const Glib::VariantBase&) { close(); });
        add_action(action_exit);

        
        auto menu = Gio::Menu::create();
        auto file_menu = Gio::Menu::create();

        file_menu->append("Open", "win.open");
        file_menu->append("Save", "win.save");
        file_menu->append("Exit", "win.exit");

        menu->append_submenu("File", file_menu);

        menu_bar.set_menu_model(menu);
        vbox.append(menu_bar);

        
        scrolled.set_child(text_view);
        text_view.set_wrap_mode(Gtk::WrapMode::WORD);

        vbox.append(scrolled);
    }

private:
    Gtk::Box vbox;
    Gtk::PopoverMenuBar menu_bar;
    Gtk::ScrolledWindow scrolled;
    Gtk::TextView text_view;
};

int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create("org.example.texteditor.ui");
    return app->make_window_and_run<TextEditorUI>(argc, argv);
}