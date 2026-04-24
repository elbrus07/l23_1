#ifndef GTKMM_EXAMPLE_HELLOWORLD_H
#define GTKMM_EXAMPLE_HELLOWORLD_H

#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/box.h>

class HelloWorld : public Gtk::Window
{
public:
    HelloWorld();
    ~HelloWorld() override;

protected:
    // Signal handlers:
    void on_view_catalog_clicked();
    void on_open_documents_clicked();

    // Member widgets:
    Gtk::Button m_button_view;
    Gtk::Button m_button_docs;
    Gtk::Box m_box;
};

#endif // GTKMM_EXAMPLE_HELLOWORLD_H