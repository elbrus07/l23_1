#include <gtkmm.h>
#include <fstream>
#include <sstream>
class MyWindow : public Gtk::Window
{
public:
    MyWindow()
    {
        set_title("Блокнот");
        set_default_size(800, 500);
        set_border_width(10);
        add(main_box);
        button_box.pack_start(btn_new);
        button_box.pack_start(btn_open);
        button_box.pack_start(btn_save);
        top_frame.add(button_box);
        text_view.set_wrap_mode(Gtk::WRAP_WORD);
        scroll.add(text_view);
        status_label.set_text("Готово");
        bottom_frame.add(status_label);
        main_box.pack_start(
            top_frame,
            Gtk::PACK_SHRINK);
        main_box.pack_start(scroll);
        main_box.pack_start(
            bottom_frame,
            Gtk::PACK_SHRINK);
        btn_new.signal_clicked().connect(
            sigc::mem_fun(
                *this,
                &MyWindow::on_new_clicked));
        btn_open.signal_clicked().connect(
            sigc::mem_fun(
                *this,
                &MyWindow::on_open_clicked));
        btn_save.signal_clicked().connect(
            sigc::mem_fun(
                *this,
                &MyWindow::on_save_clicked));
        show_all_children();
    }
private:
    void on_new_clicked()
    {
        text_view
            .get_buffer()
            ->set_text("");

        status_label.set_text(
            "Новый файл");
    }
    void on_open_clicked()
    {
        std::ifstream file("note.txt");
        if (file)
        {
            std::stringstream buffer;
            buffer << file.rdbuf();
            text_view
                .get_buffer()
                ->set_text(buffer.str());
            status_label.set_text(
                "Файл открыт");
        }
        else
        {
            status_label.set_text(
                "Файл note.txt не найден");
        }
    }

    void on_save_clicked()
    {
        std::ofstream file("note.txt");
        if (file)
        {
            Glib::ustring text =
                text_view
                    .get_buffer()
                    ->get_text();
            file << text;
            status_label.set_text(
                "Файл сохранён");
        }
    }
private:
    Gtk::Box main_box{
        Gtk::ORIENTATION_VERTICAL};
    Gtk::Box button_box{
        Gtk::ORIENTATION_HORIZONTAL};
    Gtk::Frame top_frame{"Меню"};
    Gtk::Frame bottom_frame{"Статус"};
    Gtk::Button btn_new{"Новый"};
    Gtk::Button btn_open{"Открыть"};
    Gtk::Button btn_save{"Сохранить"};
    Gtk::ScrolledWindow scroll;
    Gtk::TextView text_view;
    Gtk::Label status_label;
};
int main(int argc, char *argv[])
{
    auto app =
        Gtk::Application::create(
            argc,
            argv,
            "org.example.notepad");
    MyWindow window;
    return app->run(window);
}