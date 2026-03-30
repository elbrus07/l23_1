#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Graph {
private:
    sf::RenderWindow window;
    float centerX, centerY;
    int scale;

    float offsetX;
    float offsetY;

    std::vector<sf::Vertex> parabola;
    sf::Font font;

public:
    Graph() : window(sf::VideoMode(800, 800), "График функции") {
        centerX = window.getSize().x / 2;
        centerY = window.getSize().y / 2;

        scale = 40;

        offsetX = 0;
        offsetY = 0;

        font.loadFromFile("assets/fonts/arial.ttf");

        generateParabola();
    }

    void generateParabola() {
        parabola.clear();

        float a = 0.1f;

        for (float x = -10; x <= 10; x += 0.05f) {
            float y = a * (x - offsetX) * (x - offsetX) + offsetY;

            float screenX = centerX + x * scale;
            float screenY = centerY - y * scale;

            parabola.push_back(sf::Vertex(sf::Vector2f(screenX, screenY), sf::Color::Red));
        }
    }

    void drawAxes() {
        sf::Vertex axisX[] = {
            sf::Vertex(sf::Vector2f(0, centerY), sf::Color::White),
            sf::Vertex(sf::Vector2f(window.getSize().x, centerY), sf::Color::White)
        };

        sf::Vertex axisY[] = {
            sf::Vertex(sf::Vector2f(centerX, 0), sf::Color::White),
            sf::Vertex(sf::Vector2f(centerX, window.getSize().y), sf::Color::White)
        };

        window.draw(axisX, 2, sf::Lines);
        window.draw(axisY, 2, sf::Lines);
    }

    void drawGridAndLabels() {
        for (int i = -10; i <= 10; i++) {
            float x = centerX + i * scale;
            float y = centerY - i * scale;

            // Деления
            sf::Vertex tickX[] = {
                sf::Vertex(sf::Vector2f(x, centerY - 5), sf::Color::White),
                sf::Vertex(sf::Vector2f(x, centerY + 5), sf::Color::White)
            };

            sf::Vertex tickY[] = {
                sf::Vertex(sf::Vector2f(centerX - 5, y), sf::Color::White),
                sf::Vertex(sf::Vector2f(centerX + 5, y), sf::Color::White)
            };

            window.draw(tickX, 2, sf::Lines);
            window.draw(tickY, 2, sf::Lines);

            // Подписи
            if (i != 0) {
                sf::Text text;
                text.setFont(font);
                text.setCharacterSize(12);
                text.setFillColor(sf::Color::White);
                text.setString(std::to_string(i));

                // X подписи
                text.setPosition(x - 5, centerY + 8);
                window.draw(text);

                // Y подписи
                text.setPosition(centerX + 8, y - 8);
                window.draw(text);
            }
        }
    }

    void drawParabola() {
        if (!parabola.empty())
            window.draw(&parabola[0], parabola.size(), sf::LineStrip);
    }

    void run() {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {

                if (event.type == sf::Event::Closed)
                    window.close();

                // Движение стрелками
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Left) {
                        offsetX -= 1;
                        generateParabola();
                    }
                    if (event.key.code == sf::Keyboard::Right) {
                        offsetX += 1;
                        generateParabola();
                    }
                    if (event.key.code == sf::Keyboard::Up) {
                        offsetY += 1;
                        generateParabola();
                    }
                    if (event.key.code == sf::Keyboard::Down) {
                        offsetY -= 1;
                        generateParabola();
                    }
                }

                // ЗУМ
                if (event.type == sf::Event::MouseWheelScrolled) {
                    if (event.mouseWheelScroll.delta > 0)
                        scale += 2;
                    else if (scale > 10)
                        scale -= 2;

                    generateParabola();
                }
            }

            window.clear(sf::Color::Black);

            drawAxes();
            drawGridAndLabels();
            drawParabola();

            window.display();
        }
    }
};

int main() {
    Graph app;
    app.run();
    return 0;
}
