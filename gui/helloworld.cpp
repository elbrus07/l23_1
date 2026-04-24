#include "helloworld.h"
#include <cstdlib>
#include <iostream>

HelloWorld::HelloWorld()
: m_button_view("View catalog"),
  m_button_docs("Open Documents"),
  m_box(Gtk::Orientation::VERTICAL, 10)  // Вертикальное расположение, отступ 10px
{
    // Настройка кнопок
    m_button_view.set_margin(10);
    m_button_docs.set_margin(10);
    
    // Подключаем сигналы
    m_button_view.signal_clicked().connect(
        sigc::mem_fun(*this, &HelloWorld::on_view_catalog_clicked));
    
    m_button_docs.signal_clicked().connect(
        sigc::mem_fun(*this, &HelloWorld::on_open_documents_clicked));
    
    // Добавляем кнопки в контейнер
    m_box.append(m_button_view);
    m_box.append(m_button_docs);
    
    // Помещаем контейнер в окно
    set_child(m_box);
    
    // Устанавливаем размер окна
    set_default_size(300, 150);
    set_title("My Application");
}

HelloWorld::~HelloWorld()
{
}

void HelloWorld::on_view_catalog_clicked()
{
    std::cout << "Viewing catalog..." << std::endl;
    system("ls -l");
}

void HelloWorld::on_open_documents_clicked()
{
    std::cout << "Opening Documents..." << std::endl;
    
    // Для Linux:
    system("xdg-open ~/Documents");
    
    #ifdef _WIN32
    // Для Windows (если понадобится):
    // system("start explorer %USERPROFILE%\\Documents");
    #endif
}