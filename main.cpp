#include "helloworld.h"
#include <gtkmm/application.h>

int main(int argc, char* argv[])
{
  auto app = Gtk::Application::create("org.gtkmm.example");

  // Показывает окно и ждет его закрытия
  return app->make_window_and_run<HelloWorld>(argc, argv);
}