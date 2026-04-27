#include "helloworld.h"
#include <iostream>

HelloWorld::HelloWorld()
: m_button("Hello World") // Создает кнопку с надписью
{
  // Устанавливаем отступ вокруг кнопки
  m_button.set_margin(10);

  // При нажатии на кнопку вызывается метод on_button_clicked()
  m_button.signal_clicked().connect(sigc::mem_fun(*this,
              &HelloWorld::on_button_clicked));

  // Помещаем кнопку в окно
  set_child(m_button);
}

HelloWorld::~HelloWorld()
{
}

void HelloWorld::on_button_clicked()
{
  std::cout << "Hello World" << std::endl;
}