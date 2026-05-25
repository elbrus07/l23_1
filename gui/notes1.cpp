#include <gtkmm.h>
#include <iostream>
#include <fstream>
#include <string>

class TextEditorUI : public Gtk::ApplicationWindow {

public:
std::string filename = "New TextFile";
    TextEditorUI() {
    
    set_title("Notes: " + filename);
        //set_title("Text Editor UI (gtkmm 4)");
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
        
        auto action_font = Gio::SimpleAction::create("font");
        action_font->signal_activate().connect([this](const Glib::VariantBase&) { });
        add_action(action_font);

        auto action_height = Gio::SimpleAction::create("height");
        action_height->signal_activate().connect([this](const Glib::VariantBase&) { });
        add_action(action_height);

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

        
        
       
        auto file_view = Gio::Menu::create();
        file_view->append("Font", "win.font");
        file_view->append("Height", "win.height");
        
        menu->append_submenu("View", file_view);

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

    
    void on_file_opened(const Glib::RefPtr<Gio::AsyncResult>& result, const Glib::RefPtr<Gtk::FileDialog>& dialog) {
        try {
            auto file = dialog->open_finish(result);
            std::ifstream inFile(file->get_path());
            filename = file->get_path();
            set_title("Notes: " + filename);
            
            if (inFile) {
                std::string content((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
                text_view.get_buffer()->set_text(content);
            }
        } catch (const Glib::Error& ex) {
            std::cerr << "Ошибка при открытии: " << ex.what() << std::endl;
        }
    }

    void on_file_saved(const Glib::RefPtr<Gio::AsyncResult>& result,
                   const Glib::RefPtr<Gtk::FileDialog>& dialog) {
    try {
        auto file = dialog->save_finish(result);
        auto filename = file->get_path();

        // Получаем текст из TextView
        auto buffer = text_view.get_buffer();
        auto start = buffer->begin();
        auto end = buffer->end();
        std::string content = buffer->get_text(start, end);

        // Сохраняем в файл
        std::ofstream outFile(filename);
        if (outFile.is_open()) {
            outFile << content;
            outFile.close();
            std::cout << "Файл сохранён: " << filename << std::endl;
        } else {
            std::cerr << "Ошибка: не удалось открыть файл для записи: " << filename << std::endl;
        }
    } catch (const Gtk::DialogError& err) {
        std::cout << "Сохранение отменено." << std::endl;
    } catch (const Glib::Error& err) {
        std::cerr << "Ошибка при сохранении: " << err.what() << std::endl;
    }
}

    void saveDoc() {
    if (filename == "New TextFile"){
        auto dialog = Gtk::FileDialog::create();
        dialog->set_title("Сохранить файл");
        dialog->set_accept_label("Сохранить"); // Текст на кнопке подтверждения

    // Фильтры для сохранения
        auto filters = Gio::ListStore<Gtk::FileFilter>::create();

        auto filter_text = Gtk::FileFilter::create();
        filter_text->set_name("Текстовые файлы (*.txt)");
        filter_text->add_pattern("*.txt");
        filters->append(filter_text);

        auto filter_any = Gtk::FileFilter::create();
        filter_any->set_name("Все файлы");
        filter_any->add_pattern("*");
        filters->append(filter_any);

        dialog->set_filters(filters);

    // Показываем диалог сохранения
        dialog->save(*this, sigc::bind(sigc::mem_fun(*this, &TextEditorUI::on_file_saved), dialog));}else{
        auto buffer = text_view.get_buffer();
        auto start = buffer->begin();
        auto end = buffer->end();
        std::string content = buffer->get_text(start, end);
        std::ofstream outFile(filename);
        if (outFile.is_open()) {
            outFile << content;
            outFile.close();
            std::cout << "Файл сохранён: " << filename << std::endl;
        } else {
            std::cerr << "Ошибка: не удалось открыть файл для записи: " << filename << std::endl;
        };};
};};

int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create("org.example.texteditor.ui");
    return app->make_window_and_run<TextEditorUI>(argc, argv);
}
