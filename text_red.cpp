#include <gtkmm.h>
#include <iostream>

class SimpleEditor : public Gtk::Window {
public:
    SimpleEditor() {
        set_title("Текстовый редактор (GTKMM 4)");
        set_default_size(600, 400);

        // 
        set_child(m_main_vbox);

        // Панель кнопок 
        m_button_box.set_margin(5);
        m_button_box.set_spacing(5);

        m_btn_new.set_label("Создать");
        m_btn_open.set_label("Открыть");
        m_btn_save.set_label("Сохранить");

        m_button_box.append(m_btn_new);
        m_button_box.append(m_btn_open);
        m_button_box.append(m_btn_save);

        // Добавляем панель в главный контейнер 
        m_main_vbox.append(m_button_box);

        //поле ввода текста
        m_text_view.set_expand(true); // Занимает все свободное место
        m_scrolled_window.set_child(m_text_view);
        m_scrolled_window.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
        m_scrolled_window.set_expand(true);
        
        m_main_vbox.append(m_scrolled_window);

        //  Сигналы
        m_btn_new.signal_clicked().connect(sigc::mem_fun(*this, &SimpleEditor::on_new_clicked));
        m_btn_open.signal_clicked().connect(sigc::mem_fun(*this, &SimpleEditor::on_open_clicked));
        m_btn_save.signal_clicked().connect(sigc::mem_fun(*this, &SimpleEditor::on_save_clicked));
    }

protected:
    void on_new_clicked() {
        m_text_view.get_buffer()->set_text(""); 
    }

    void on_open_clicked() {
        std::cout << "Логика открытия файла..." << std::endl;
    }

    void on_save_clicked() {
        std::cout << "Логика сохранения файла..." << std::endl;
    }

    Gtk::Box m_main_vbox{Gtk::Orientation::VERTICAL};
    Gtk::Box m_button_box{Gtk::Orientation::HORIZONTAL};
    Gtk::Button m_btn_new, m_btn_open, m_btn_save;
    Gtk::ScrolledWindow m_scrolled_window;
    Gtk::TextView m_text_view;
};

int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create("org.gtkmm.example.editor");
    return app->make_window_and_run<SimpleEditor>(argc, argv);
}