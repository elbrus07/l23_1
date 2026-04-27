#include <gtkmm.h>
class MyWindow : public Gtk::Window{
public:
  MyWindow(){
    set_title("Блокнот");
    set_default_size(800,500);
    set_border_width(10);
    add(main_box);
    button_box.pack_start(btn_new);
    button_box.pack_start(btn_open);
    button_box.pack_start(btn_save);
    top_frame.add(button_box);
    text_view.set_wrap_mode(Gtk::WRAP_WORD);
    scroll.add(text_view);
    status_label.set_text("Ujnj");
    bottom_frame.add(status_label);
    main_box.pack_start(top_frame, Gtk::PACK_SHRINK);
    main_box.pack_start(scroll);
    main_box.pack_start(bottom_frame, Gtk;;PACK_SHRINK);
    show_all_children();
  }
private:
  
    
