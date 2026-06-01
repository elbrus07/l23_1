
#include <gtkmm.h>
#include <fstream>
#include <regex>
#include <array>

class ColorEditWindow : public Gtk::ApplicationWindow
{
public:
    ColorEditWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
    : Gtk::ApplicationWindow(cobject)
    {
        setup_ui();
        setup_tags();
        connect_signals();
    }

    static Glib::RefPtr<ColorEditWindow> create(const Glib::RefPtr<Gtk::Application>& app)
    {
        auto builder = Gtk::Builder::create();
        auto window = Glib::RefPtr<ColorEditWindow>(new ColorEditWindow(nullptr, builder));
        window->set_application(app);
        return window;
    }

private:
    // Настройка интерфейса 
    void setup_ui()
    {
        set_title("ColorEdit — редактор с цветами");
        set_default_size(950, 650);

        // Главный вертикальный контейнер
        m_main_box.set_orientation(Gtk::Orientation::VERTICAL);
        m_main_box.set_margin(6);
        set_child(m_main_box);

        // Панель инструментов (кнопки слева направо)
        m_toolbar.set_orientation(Gtk::Orientation::HORIZONTAL);
        m_toolbar.set_spacing(4);
        m_toolbar.set_hexpand(true);

        m_btn_open.set_label("📂 Открыть");
        m_btn_create.set_label("📄 Создать");
        m_btn_save.set_label("💾 Сохранить");
        m_btn_toggle.set_label("✨ Подсветка: ВКЛ");
        m_btn_toggle.set_has_frame(true);

        // Цветные кнопки: оранжевый, жёлтый, красный
        setup_color_button(m_btn_orange, "#FF9800", "🟠");
        setup_color_button(m_btn_yellow, "#FFEB3B", "🟡");
        m_btn_yellow.set_label("🟡");
        setup_color_button(m_btn_red, "#F44336", "🔴");

        // Добавляем кнопки в тулбар
        m_toolbar.append(m_btn_open);
        m_toolbar.append(m_btn_create);
        m_toolbar.append(m_btn_save);
        m_toolbar.append(m_btn_toggle);
        m_toolbar.append(m_btn_orange);
        m_toolbar.append(m_btn_yellow);
        m_toolbar.append(m_btn_red);

        m_main_box.append(m_toolbar);

        // Область редактирования
        m_text_view.set_wrap_mode(Gtk::WrapMode::WORD);
        m_text_view.set_monospace(true);
        m_text_view.set_vexpand(true);
        m_text_view.set_hexpand(true);

        m_scroll.set_child(m_text_view);
        m_scroll.set_vexpand(true);
        m_main_box.append(m_scroll);

        // Поле ввода снизу 
        m_input_box.set_orientation(Gtk::Orientation::HORIZONTAL);
        m_input_box.set_spacing(6);

        m_prompt_label.set_text("> ");
        m_prompt_label.set_margin_end(4);

        m_entry.set_placeholder_text("Введите текст или команду...");
        m_entry.set_hexpand(true);
        m_entry.set_max_width_chars(80);

        m_input_box.append(m_prompt_label);
        m_input_box.append(m_entry);
        m_main_box.append(m_input_box);
    }

    void setup_color_button(Gtk::Button& btn, const std::string& color, const std::string& label)
    {
        btn.set_label(label);
        // Добавляем стиль через CSS для цвета фона
        auto css = Gtk::CssProvider::create();
        css->load_from_data(
            "button { background-color: " + color + "; color: black; font-weight: bold; }"
            "button:hover { background-color: " + darken_color(color) + "; }"
        );
        btn.get_style_context()->add_provider(css, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    }

    // Затемнение цвета для hover-эффекта 
    std::string darken_color(const std::string& hex)
    {
        // убираем яркость на 20%
        return hex;
    }

    //  Теги для форматирования
    void setup_tags()
    {
        auto buffer = m_text_view.get_buffer();

        // Теги подсветки синтаксиса
        m_keyword_tag = buffer->create_tag("keyword");
        m_keyword_tag->property_weight() = Pango::Weight::BOLD;
        m_keyword_tag->property_foreground() = "#1976D2"; // синий

        // Цветные теги для выделения
        m_tag_orange = buffer->create_tag("orange");
        m_tag_orange->property_foreground() = "#FF9800";

        m_tag_yellow = buffer->create_tag("yellow");
        m_tag_yellow->property_foreground() = "#9E9E00"; // тёмно-жёлтый для читаемости

        m_tag_red = buffer->create_tag("red");
        m_tag_red->property_foreground() = "#F44336";

        // Тег для фона (маркер)
        m_tag_marker = buffer->create_tag("marker");
        m_tag_marker->property_background() = "#FFF9C4"; // светло-жёлтый фон
    }

    // Подключение сигналов 
    void connect_signals()
    {
        m_btn_open.signal_clicked().connect(sigc::mem_fun(*this, &ColorEditWindow::on_open));
        m_btn_create.signal_clicked().connect(sigc::mem_fun(*this, &ColorEditWindow::on_create));
        m_btn_save.signal_clicked().connect(sigc::mem_fun(*this, &ColorEditWindow::on_save));
        m_btn_toggle.signal_clicked().connect(sigc::mem_fun(*this, &ColorEditWindow::on_toggle_highlight));
        m_btn_orange.signal_clicked().connect(sigc::mem_fun(*this, &ColorEditWindow::on_apply_orange));
        m_btn_yellow.signal_clicked().connect(sigc::mem_fun(*this, &ColorEditWindow::on_apply_yellow));
        m_btn_red.signal_clicked().connect(sigc::mem_fun(*this, &ColorEditWindow::on_apply_red));

        // Обработка нажатия Enter в нижнем поле ввода
        m_entry.signal_activate().connect(sigc::mem_fun(*this, &ColorEditWindow::on_entry_activate));

        // Подсветка при изменении текста (с задержкой)
        m_text_view.get_buffer()->signal_changed().connect(
            sigc::mem_fun(*this, &ColorEditWindow::schedule_highlight));
    }

    // Обработчики кнопок 
    void on_open()
    {
        auto dialog = Gtk::FileDialog::create();
        dialog->set_title("Открыть файл");
        dialog->open(
            *this,
            [this](const Glib::RefPtr<Gio::File>& file) {
                if (file) {
                    try {
                        auto [contents, etag] = file->load_contents();
                        std::string text(reinterpret_cast<const char*>(contents.data()), contents.size());
                        m_text_view.get_buffer()->set_text(text);
                        m_current_path = file->get_path();
                        show_status("Открыт: " + m_current_path);
                    } catch (const Glib::Error& e) {
                        show_status("Ошибка: " + e.what(), true);
                    }
                }
            },
            [](const Glib::Error&){ /* отмена */ }
        );
    }

    void on_create()
    {
        if (confirm_discard()) {
            m_text_view.get_buffer()->set_text("");
            m_current_path.clear();
            m_entry.set_text("");
            show_status("Новый документ");
        }
    }

    void on_save()
    {
        if (m_current_path.empty()) {
            on_save_as();
            return;
        }
        save_to_path(m_current_path);
    }

    void on_save_as()
    {
        auto dialog = Gtk::FileDialog::create();
        dialog->set_title("Сохранить как...");
        dialog->save(
            *this,
            [this](const Glib::RefPtr<Gio::File>& file) {
                if (file) {
                    m_current_path = file->get_path();
                    save_to_path(m_current_path);
                }
            }
        );
    }

    void save_to_path(const std::string& path)
    {
        try {
            auto buffer = m_text_view.get_buffer();
            auto file = Gio::File::create_for_path(path);
            auto text = buffer->get_text();
            file->replace_contents(text, "");
            show_status("Сохранён: " + path);
        } catch (const Glib::Error& e) {
            show_status("Ошибка сохранения: " + e.what(), true);
        }
    }

    // Подсветка синтаксиса  
    void on_toggle_highlight()
    {
        m_highlight_enabled = !m_highlight_enabled;
        m_btn_toggle.set_label(m_highlight_enabled ? "✨ Подсветка: ВКЛ" : "⚪ Подсветка: ВЫКЛ");
        if (m_highlight_enabled) {
            do_highlight();
        } else {
            clear_highlight();
        }
    }

    void schedule_highlight()
    {
        if (!m_highlight_enabled) return;
        if (m_pending_highlight) return;

        m_pending_highlight = true;
        Glib::Timeout::connect(
            [this]() {
                if (m_highlight_enabled) do_highlight();
                m_pending_highlight = false;
                return false;
            },
            250 // задержка 250 мс
        );
    }

    void do_highlight()
    {
        auto buffer = m_text_view.get_buffer();
        clear_highlight();

        std::string text = buffer->get_text();
        // Простой список ключевых слов для подсветки
        static const std::array<std::string, 8> keywords = {
            "if", "else", "for", "while", "return", "class", "int", "void"
        };

        for (const auto& kw : keywords) {
            std::regex word_regex("\\b" + kw + "\\b");
            auto begin = std::sregex_iterator(text.begin(), text.end(), word_regex);
            auto end = std::sregex_iterator();

            for (auto it = begin; it != end; ++it) {
                auto match = *it;
                auto start_iter = buffer->get_iter_at_offset(match.position());
                auto end_iter = buffer->get_iter_at_offset(match.position() + match.length());
                buffer->apply_tag(m_keyword_tag, start_iter, end_iter);
            }
        }
    }

    void clear_highlight()
    {
        auto buffer = m_text_view.get_buffer();
        buffer->remove_tag(m_keyword_tag, buffer->begin(), buffer->end());
    }

    // Применение цветов к выделению 
    void apply_color_tag(const Glib::RefPtr<Gtk::TextTag>& tag)
    {
        auto buffer = m_text_view.get_buffer();
        Gtk::TextIter start, end;

        if (buffer->get_selection_bounds(start, end)) {
            // Если тег уже применён — убираем, иначе — добавляем
            if (start.has_tag(tag) && end.has_tag(tag)) {
                buffer->remove_tag(tag, start, end);
            } else {
                buffer->apply_tag(tag, start, end);
            }
        } else {
            // Если нет выделения — применяем к позиции курсора (для будущего ввода)
            auto cursor = buffer->get_insert();
            buffer->place_cursor(buffer->get_iter_at_mark(cursor));
        }
    }

    void on_apply_orange() { apply_color_tag(m_tag_orange); }
    void on_apply_yellow() { apply_color_tag(m_tag_yellow); }
    void on_apply_red()    { apply_color_tag(m_tag_red); }

    // Нижнее поле ввода 
    void on_entry_activate()
    {
        std::string cmd = m_entry.get_text();
        if (cmd.empty()) return;

        auto buffer = m_text_view.get_buffer();
        buffer->insert(buffer->end(), cmd + "\n");

        // Простые команды
        if (cmd == "/clear" || cmd == "очистить") {
            buffer->set_text("");
        } else if (cmd.starts_with("/color ")) {
            // Команда для быстрой смены цвета 
            show_status("Команда: " + cmd);
        }

        m_entry.set_text("");
        m_text_view.scroll_to(buffer->end(), 0.0);
    }

    //  Вспомогательные методы 
    bool confirm_discard()
    {
        // Упрощённо: всегда разрешаем 
        return true;
    }

    void show_status(const std::string& msg, bool error = false)
    {
        m_entry.set_placeholder_text(msg);
        if (error) {
            // Подсветка ошибки
            auto css = m_entry.get_style_context()->get_provider_for_screen(get_screen());
        }
        // Сброс через 3 секунды
        Glib::Timeout::connect([this, msg]() {
            if (m_entry.get_placeholder_text() == msg) {
                m_entry.set_placeholder_text("Введите текст или команду...");
            }
            return false;
        }, 3000);
    }

    //  Поля класса 
    Gtk::Box m_main_box;
    Gtk::Box m_toolbar;
    Gtk::Box m_input_box;

    Gtk::Button m_btn_open, m_btn_create, m_btn_save, m_btn_toggle;
    Gtk::Button m_btn_orange, m_btn_yellow, m_btn_red;

    Gtk::ScrolledWindow m_scroll;
    Gtk::TextView m_text_view;

    Gtk::Label m_prompt_label;
    Gtk::Entry m_entry;

    // Теги
    Glib::RefPtr<Gtk::TextTag> m_keyword_tag;
    Glib::RefPtr<Gtk::TextTag> m_tag_orange, m_tag_yellow, m_tag_red, m_tag_marker;

    // Состояние
    std::string m_current_path;
    bool m_highlight_enabled = true;
    bool m_pending_highlight = false;
};

// ───────── Точка входа ─────────
int main(int argc, char* argv[])
{
    auto app = Gtk::Application::create("org.coloredit.app");

    // Регистрация типа для возможного использования с Builder
    Gtk::Window::register_derived_type("ColorEditWindow",
        Gtk::DerivedWidgetCreator<ColorEditWindow>());

    auto window = ColorEditWindow::create(app);
    return app->run(*window, argc, argv);
}