#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include <iostream>
#include <string>
// Программа рисует оси координат и график функции sin(x)
int main()
{
    // окно
    sf::RenderWindow window(sf::VideoMode({800, 600}), "график функции синуса");
    // центр координат
    int centerX = 400;
    int centerY = 300;
    // масштаб графика
    float scale = 50.0f;
    std::vector<sf::Vertex> graphPoints;
    // точки гафика
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
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        window.clear(sf::Color::White);
        // X
        sf::Vertex xAxis[2];
        xAxis[0].position = sf::Vector2f(0, centerY);
        xAxis[1].position = sf::Vector2f(800, centerY);
        xAxis[0].color = sf::Color::Black;
        xAxis[1].color = sf::Color::Black;
        // Y
        sf::Vertex yAxis[2];
        yAxis[0].position = sf::Vector2f(centerX, 0);
        yAxis[1].position = sf::Vector2f(centerX, 600);
        yAxis[0].color = sf::Color::Black;
        yAxis[1].color = sf::Color::Black;
        window.draw(xAxis, 2, sf::PrimitiveType::Lines);
        window.draw(yAxis, 2, sf::PrimitiveType::Lines);
        if (graphPoints.size() > 1)
        {
            window.draw(&graphPoints[0], graphPoints.size(), sf::PrimitiveType::LineStrip);
        }
        window.display();
    }
    return 0;
}
