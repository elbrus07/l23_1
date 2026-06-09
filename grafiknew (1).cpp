#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <string>
int main()
{
    const int WIDTH = 1200;
    const int HEIGHT = 800;
    sf::RenderWindow window(
        sf::VideoMode(WIDTH, HEIGHT),
        "график функции");
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
        return -1;
    float scale = 50.0f;
    float offsetX = 0.0f;
    float offsetY = 0.0f;
    int functionType = 0;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseWheelScrolled)
            {
                if (event.mouseWheelScroll.delta > 0)
                    scale *= 1.1f;
                else
                    scale *= 0.9f;
                if (scale < 10)
                    scale = 10;
                if (scale > 500)
                    scale = 500;
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Num1)
                    functionType = 0;
                if (event.key.code == sf::Keyboard::Num2)
                    functionType = 1;
                if (event.key.code == sf::Keyboard::Num3)
                    functionType = 2;
                if (event.key.code == sf::Keyboard::Num4)
                    functionType = 3;
                if (event.key.code == sf::Keyboard::R)
                {
                    scale = 50.0f;
                    offsetX = 0;
                    offsetY = 0;
                }
            }
        }
        float moveSpeed = 5.0f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            offsetX += moveSpeed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            offsetX -= moveSpeed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            offsetY += moveSpeed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            offsetY -= moveSpeed;
        std::string functionName;
        switch (functionType)
        {
        case 0:
            functionName = "sin(x)";
            break;
        case 1:
            functionName = "cos(x)";
            break;
        case 2:
            functionName = "tan(x)";
            break;
        case 3:
            functionName = "x^2";
            break;
        }
        window.setTitle(
            "функция: " + functionName +
            " | 1-sin 2-cos 3-tan 4-x^2 | R-сброс ");

        window.clear(sf::Color::White);

        float centerX = WIDTH / 2.0f + offsetX;
        float centerY = HEIGHT / 2.0f + offsetY;
        // Ось X
        sf::Vertex xAxis[] =
            {
                sf::Vertex(sf::Vector2f(0, centerY), sf::Color::Black),
                sf::Vertex(sf::Vector2f(WIDTH, centerY), sf::Color::Black)};
        // Ось Y
        sf::Vertex yAxis[] =
            {
                sf::Vertex(sf::Vector2f(centerX, 0), sf::Color::Black),
                sf::Vertex(sf::Vector2f(centerX, HEIGHT), sf::Color::Black)};
        window.draw(xAxis, 2, sf::Lines);
        window.draw(yAxis, 2, sf::Lines);
        // Деления по X
        for (int i = -50; i <= 50; i++)
        {
            float x = centerX + i * scale;
            sf::Vertex tick[] =
                {
                    sf::Vertex(sf::Vector2f(x, centerY - 5), sf::Color::Black),
                    sf::Vertex(sf::Vector2f(x, centerY + 5), sf::Color::Black)};
            window.draw(tick, 2, sf::Lines);
            if (i != 0)
            {
                sf::Text label;
                label.setFont(font);
                label.setCharacterSize(12);
                label.setFillColor(sf::Color::Black);
                label.setString(std::to_string(i));
                label.setPosition(x - 8, centerY + 8);
                window.draw(label);
            }
        }
        // Деления по оси Y
        for (int i = -30; i <= 30; i++)
        {
            float y = centerY - i * scale;
            sf::Vertex tick[] =
                {
                    sf::Vertex(sf::Vector2f(centerX - 5, y), sf::Color::Black),
                    sf::Vertex(sf::Vector2f(centerX + 5, y), sf::Color::Black)};
            window.draw(tick, 2, sf::Lines);
            if (i != 0)
            {
                sf::Text label;
                label.setFont(font);
                label.setCharacterSize(12);
                label.setFillColor(sf::Color::Black);
                label.setString(std::to_string(i));
                label.setPosition(centerX + 8, y - 8);
                window.draw(label);
            }
        }
        std::vector<sf::Vertex> graphPoints;
        for (float x = -50.0f; x <= 50.0f; x += 0.01f)
        {
            float y = 0.0f;
            switch (functionType)
            {
            case 0:
                y = sin(x);
                break;
            case 1:
                y = cos(x);
                break;
            case 2:
                y = tan(x);
                if (fabs(y) > 20)
                    continue;
                break;
            case 3:
                y = x * x;
                break;
            }
            float screenX = centerX + x * scale;
            float screenY = centerY - y * scale;
            graphPoints.push_back(
                sf::Vertex(
                    sf::Vector2f(screenX, screenY),
                    sf::Color::Red));
        }
        if (!graphPoints.empty())
        {
            window.draw(
                &graphPoints[0],
                graphPoints.size(),
                sf::LineStrip);
        }
        window.display();
    }
    return 0;
}