#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include <iostream>
#include <string>

// Простая программа, которая рисует оси координат и график функции sin(x)

int main()
{
    // создаем окно
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Graph");

    // центр координат
    int centerX = 400;
    int centerY = 300;

    // масштаб графика
    float scale = 50.0f;

    // вектор для хранения точек графика
    std::vector<sf::Vertex> graphPoints;

    // создаем точки графика
    for (float x = -10; x <= 10; x += 0.1f)
    {
        float y = sin(x);

        float screenX = centerX + x * scale;
        float screenY = centerY - y * scale;

        sf::Vertex v;
        v.position = sf::Vector2f(screenX, screenY);
        v.color = sf::Color::Red;

        graphPoints.push_back(v);
    }

    // главный цикл программы
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color::White);

        // ось X
        sf::Vertex xAxis[2];
        xAxis[0].position = sf::Vector2f(0, centerY);
        xAxis[1].position = sf::Vector2f(800, centerY);
        xAxis[0].color = sf::Color::Black;
        xAxis[1].color = sf::Color::Black;

        // ось Y
        sf::Vertex yAxis[2];
        yAxis[0].position = sf::Vector2f(centerX, 0);
        yAxis[1].position = sf::Vector2f(centerX, 600);
        yAxis[0].color = sf::Color::Black;
        yAxis[1].color = sf::Color::Black;

        // рисуем оси
        window.draw(xAxis, 2, sf::PrimitiveType::Lines);
        window.draw(yAxis, 2, sf::PrimitiveType::Lines);

        // рисуем график
        if (graphPoints.size() > 1)
        {
            window.draw(&graphPoints[0], graphPoints.size(), sf::PrimitiveType::LineStrip);
        }

        window.display();
    }

    return 0;
}
