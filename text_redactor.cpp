#include <gtkmm.h>

class EditorToolbar : public Gtk::Window {
public:
    EditorToolbar() {
        set_title("Текстовый редактор - Панель инструментов");
        set_default_size(800, 150); // Широкое окно, небольшая высота
        set_resizable(true);

        Gtk::Box *main_box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 0);
        set_child(*main_box);

        m_toolbar = Gtk::make_managed<Gtk::Toolbar>();
        main_box->append(*m_toolbar);

        auto icon_theme = Gtk::IconTheme::get_for_display(get_display());
        
        // 1. Кнопка "Создать"
        auto new_btn = Gtk::make_managed<Gtk::ToolButton>();
        new_btn->set_icon_name("document-new");
        new_btn->set_tooltip_text("Создать новый файл");
        new_btn->signal_clicked().connect([]() {
            std::cout << "Нажата кнопка: Создать" << std::endl;
        });
        m_toolbar->append(*new_btn);

        // 2. Кнопка "Открыть"
        auto open_btn = Gtk::make_managed<Gtk::ToolButton>();
        open_btn->set_icon_name("document-open");
        open_btn->set_tooltip_text("Открыть файл");
        open_btn->signal_clicked().connect([]() {
            std::cout << "Нажата кнопка: Открыть" << std::endl;
        });
        m_toolbar->append(*open_btn);

        // 3. Кнопка "Сохранить"
        auto save_btn = Gtk::make_managed<Gtk::ToolButton>();
        save_btn->set_icon_name("document-save");
        save_btn->set_tooltip_text("Сохранить");
        save_btn->signal_clicked().connect([]() {
            std::cout << "Нажата кнопка: Сохранить" << std::endl;
        });
        m_toolbar->append(*save_btn);

        m_toolbar->append(*Gtk::make_managed<Gtk::SeparatorToolItem>());

        // 5. Кнопка "Вырезать"
        auto cut_btn = Gtk::make_managed<Gtk::ToolButton>();
        cut_btn->set_icon_name("edit-cut");
        cut_btn->set_tooltip_text("Вырезать");
        cut_btn->signal_clicked().connect([]() {
            std::cout << "Нажата кнопка: Вырезать" << std::endl;
        });
        m_toolbar->append(*cut_btn);

        // 6. Кнопка "Копировать"
        auto copy_btn = Gtk::make_managed<Gtk::ToolButton>();
        copy_btn->set_icon_name("edit-copy");
        copy_btn->set_tooltip_text("Копировать");
        copy_btn->signal_clicked().connect([]() {
            std::cout << "Нажата кнопка: Копировать" << std::endl;
        });
        m_toolbar->append(*copy_btn);

        // 7. Кнопка "Вставить"
        auto paste_btn = Gtk::make_managed<Gtk::ToolButton>();
        paste_btn->set_icon_name("edit-paste");
        paste_btn->set_tooltip_text("Вставить");
        paste_btn->signal_clicked().connect([]() {
            std::cout << "Нажата кнопка: Вставить" << std::endl;
        });
        m_toolbar->append(*paste_btn);

        m_toolbar->append(*Gtk::make_managed<Gtk::SeparatorToolItem>());

        // 9. Кнопка "Отменить"
        auto undo_btn = Gtk::make_managed<Gtk::ToolButton>();
        undo_btn->set_icon_name("edit-undo");
        undo_btn->set_tooltip_text("Отменить");
        undo_btn->signal_clicked().connect([]() {
            std::cout << "Нажата кнопка: Отменить" << std::endl;
        });
        m_toolbar->append(*undo_btn);

        // 10. Кнопка "Повторить"
        auto redo_btn = Gtk::make_managed<Gtk::ToolButton>();
        redo_btn->set_icon_name("edit-redo");
        redo_btn->set_tooltip_text("Повторить");
        redo_btn->signal_clicked().connect([]() {
            std::cout << "Нажата кнопка: Повторить" << std::endl;
        });
        m_toolbar->append(*redo_btn);

        m_toolbar->append(*Gtk::make_managed<Gtk::SeparatorToolItem>());

        // 12. Кнопка "Поиск"
        auto find_btn = Gtk::make_managed<Gtk::ToolButton>();
        find_btn->set_icon_name("edit-find");
        find_btn->set_tooltip_text("Поиск");
        find_btn->signal_clicked().connect([]() {
            std::cout << "Нажата кнопка: Поиск" << std::endl;
        });
        m_toolbar->append(*find_btn);

        // 13. Кнопка "Настройки"
        auto settings_btn = Gtk::make_managed<Gtk::ToolButton>();
        settings_btn->set_icon_name("preferences-system");
        settings_btn->set_tooltip_text("Настройки");
        settings_btn->signal_clicked().connect([]() {
            std::cout << "Нажата кнопка: Настройки" << std::endl;
        });
        m_toolbar->append(*settings_btn);

        // Добавляем текстовые кнопки-дублёры (простые Gtk::Button)
        std::vector<std::string> labels = {"Жирный", "Курсив", "Подчёркнутый", "Цвет"};
        for (const auto& label : labels) {
            auto btn = Gtk::make_managed<Gtk::Button>(label);
            btn->signal_clicked().connect([label]() {
                std::cout << "Нажата кнопка: " << label << std::endl;
            });
            button_box->append(*btn);
        }
    }

private:
    Gtk::Toolbar* m_toolbar = nullptr;
};

int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create("org.gtkmm.example.editor_buttons");

    EditorToolbar window;

    return app->run(window, argc, argv);
}
