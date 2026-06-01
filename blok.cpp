#include <gtkmm.h>
#include <fstream>
#include <sstream>
#include <regex>
#include <string>

class EditorWindow : public Gtk::Window
{
public:
    EditorWindow()
    {
        setup_ui();
        setup_signals();
        setup_css_provider();
        update_font_size();
    }

private:
    // ------------------------------------------------------------------
    // Инициализация интерфейса
    // ------------------------------------------------------------------
    void setup_ui()
    {
        set_title("Текстовый редактор");
        set_default_size(900, 600);
        set_child(main_box);

        btn_new.set_label("Новый");
        btn_open.set_label("Открыть");
        btn_save.set_label("Сохранить");
        btn_save_as.set_label("Сохранить как");
        size_label.set_text("Размер:");
        
        font_size.set_range(8, 48);
        font_size.set_value(14);
        font_size.set_increments(1, 2);

        toolbar.append(btn_new);
        toolbar.append(btn_open);
        toolbar.append(btn_save);
        toolbar.append(btn_save_as);
        toolbar.append(size_label);
        toolbar.append(font_size);

        buffer = Gtk::TextBuffer::create();
        text_view.set_buffer(buffer);
        text_view.set_wrap_mode(Gtk::WrapMode::WORD);
        scroll.set_child(text_view);
        scroll.set_expand(true);

        main_box.append(toolbar);
        main_box.append(scroll);

        // Тег подсветки синтаксиса
        keyword_tag = buffer->create_tag();
        keyword_tag->property_weight() = Pango::Weight::BOLD;
    }

    // ------------------------------------------------------------------
    // Привязка сигналов
    // ------------------------------------------------------------------
    void setup_signals()
    {
        btn_new.signal_clicked().connect(sigc::mem_fun(*this, &EditorWindow::on_new_clicked));
        btn_open.signal_clicked().connect(sigc::mem_fun(*this, &EditorWindow::on_open_clicked));
        btn_save.signal_clicked().connect(sigc::mem_fun(*this, &EditorWindow::on_save_clicked));
        btn_save_as.signal_clicked().connect(sigc::mem_fun(*this, &EditorWindow::on_save_as_clicked));
        font_size.signal_value_changed().connect(sigc::mem_fun(*this, &EditorWindow::update_font_size));
        buffer->signal_changed().connect(sigc::mem_fun(*this, &EditorWindow::highlight_keywords));
    }

    // ------------------------------------------------------------------
    // CSS провайдер (создается один раз)
    // ------------------------------------------------------------------
    void setup_css_provider()
    {
        css_provider = Gtk::CssProvider::create();
        Gtk::StyleContext::add_provider_for_display(
            Gdk::Display::get_default(),
            css_provider,
            GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    }

    // ------------------------------------------------------------------
    // Логика работы
    // ------------------------------------------------------------------
    void on_new_clicked()
    {
        buffer->set_text("");
        current_file.clear();
    }

    void on_open_clicked()
    {
        auto dialog = Gtk::FileChooserNative::create(
            "Открыть файл", *this,
            Gtk::FileChooser::Action::OPEN, "Открыть", "Отмена");

        dialog->signal_response().connect([this, dialog](int response) {
            if (response == Gtk::ResponseType::ACCEPT) {
                if (auto file = dialog->get_file(); file) {
                    current_file = file->get_path();
                    std::ifstream in(current_file);
                    if (in) {
                        std::stringstream ss;
                        ss << in.rdbuf();
                        buffer->set_text(ss.str());
                    }
                }
            }
        });
        dialog->show();
    }

    void on_save_clicked()
    {
        if (current_file.empty()) {
            on_save_as_clicked();
            return;
        }
        save_file(current_file);
    }

    void on_save_as_clicked()
    {
        auto dialog = Gtk::FileChooserNative::create(
            "Сохранить файл", *this,
            Gtk::FileChooser::Action::SAVE, "Сохранить", "Отмена");

        dialog->signal_response().connect([this, dialog](int response) {
            if (response == Gtk::ResponseType::ACCEPT) {
                if (auto file = dialog->get_file(); file) {
                    current_file = file->get_path();
                    save_file(current_file);
                }
            }
        });
        dialog->show();
    }

    void save_file(const std::string& path)
    {
        std::ofstream out(path);
        if (out) {
            out << buffer->get_text();
        }
    }

    void update_font_size()
    {
        int size = static_cast<int>(font_size.get_value());
        std::string css = "textview { font-size: " + std::to_string(size) + "pt; }";
        css_provider->load_from_string(css);
    }

    void highlight_keywords()
    {
        auto start = buffer->begin();
        auto end = buffer->end();
        buffer->remove_tag(keyword_tag, start, end);

        std::string text = buffer->get_text();
        // Регулярное выражение компилируется один раз и кэшируется
        static const std::regex keywords_reg("\\b(if|else|for|while|return|class)\\b");

        auto words_begin = std::sregex_iterator(text.begin(), text.end(), keywords_reg);
        auto words_end = std::sregex_iterator();

        for (auto it = words_begin; it != words_end; ++it) {
            auto match = *it;
            auto begin_iter = buffer->get_iter_at_offset(match.position());
            auto finish_iter = buffer->get_iter_at_offset(match.position() + match.length());
            buffer->apply_tag(keyword_tag, begin_iter, finish_iter);
        }
    }

private:
    // Элементы интерфейса
    Gtk::Box main_box{Gtk::Orientation::VERTICAL};
    Gtk::Box toolbar{Gtk::Orientation::HORIZONTAL};
    Gtk::Button btn_new;
    Gtk::Button btn_open;
    Gtk::Button btn_save;
    Gtk::Button btn_save_as;
    Gtk::Label size_label;
    Gtk::SpinButton font_size;
    Gtk::ScrolledWindow scroll;
    Gtk::TextView text_view;
    
    Glib::RefPtr<Gtk::TextBuffer> buffer;
    Glib::RefPtr<Gtk::TextTag> keyword_tag;
    Glib::RefPtr<Gtk::CssProvider> css_provider; // Вынесен в члены класса
    std::string current_file;
};

int main(int argc, char* argv[])
{
    auto app = Gtk::Application::create("org.example.editor");
    return app->make_window_and_run<EditorWindow>(argc, argv);
}