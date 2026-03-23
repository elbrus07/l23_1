#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Graph {
private:
    sf::RenderWindow window;
    float centerX, centerY;
    int scale; // пикселей на 1 единицу

    std::vector<sf::Vertex> parabola;
    sf::Font font;

public:
    Graph() : window(sf::VideoMode(600, 600), "График функции"), scale(40) {
        centerX = window.getSize().x / 2.0f;
        centerY = window.getSize().y / 2.0f;

        //тут шрифт(лежит рядом с исполняемым файлом)
        font.loadFromFile("arial.ttf");

        Parabola();
    }

    void Parabola() {
        float a = 0.1f;

        for (float x = -10; x <= 10; x += 0.1f) {
            float y = a * x * x;

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
        int maxUnits = 10;

        for (int i = -maxUnits; i <= maxUnits; i++) {

            float x = centerX + i * scale;
            float y = centerY - i * scale;

            
            sf::Vertex tickX[] = {
                sf::Vertex(sf::Vector2f(x, centerY - 5), sf::Color::White),
                sf::Vertex(sf::Vector2f(x, centerY + 5), sf::Color::White)
            };

            window.draw(tickX, 2, sf::Lines);

        
            sf::Vertex tickY[] = {
                sf::Vertex(sf::Vector2f(centerX - 5, y), sf::Color::White),
                sf::Vertex(sf::Vector2f(centerX + 5, y), sf::Color::White)
            };

            window.draw(tickY, 2, sf::Lines);

        

            if (i != 0) {
                sf::Text text;
                text.setFont(font);
                text.setString(std::to_string(i));
                text.setCharacterSize(14);
                text.setFillColor(sf::Color::White);

                //подписи по X
                text.setPosition(x - 10, centerY + 8);
                window.draw(text);

                //подписи по Y
                text.setPosition(centerX + 8, y - 10);
                window.draw(text);
            }
        }
    }

    void drawParabola() {
        window.draw(&parabola[0], parabola.size(), sf::LineStrip);
    }

    void run() {
        while (window.isOpen()) {
            sf::Event event;

            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
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