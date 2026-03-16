#include <SFML/Graphics.hpp>
#include <vector>

int main() {
    sf::RenderWindow window(sf::VideoMode(400, 400), "Координатные оси");

    float centerX = window.getSize().x / 2.0f;
    float centerY = window.getSize().y / 2.0f;

    // х
    sf::Vertex axisX[] = {
        sf::Vertex(sf::Vector2f(0, centerY), sf::Color::White),
        sf::Vertex(sf::Vector2f(window.getSize().x, centerY), sf::Color::White)
    };

    // у
    sf::Vertex axisY[] = {
        sf::Vertex(sf::Vector2f(centerX, 0), sf::Color::White),
        sf::Vertex(sf::Vector2f(centerX, window.getSize().y), sf::Color::White)
    };

    //функция(парабола)
    float a = 0.01f;
    std::vector<sf::Vertex> parabola;

    for (float x = -200; x <= 200; x += 1) {
        float y = a * x * x;

        float screenX = centerX + x;
        float screenY = centerY - y;

        parabola.push_back(sf::Vertex(sf::Vector2f(screenX, screenY), sf::Color::Red));
    }

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        //оси
        window.draw(axisX, 2, sf::Lines);
        window.draw(axisY, 2, sf::Lines);


        int step = 20;      // расстояние между делениями
        int tickSize = 5;   // размер деления

        //дления по X
        for (int x = 0; x <= window.getSize().x; x += step) {

            sf::Vertex tick[] = {
                sf::Vertex(sf::Vector2f(x, centerY - tickSize), sf::Color::White),
                sf::Vertex(sf::Vector2f(x, centerY + tickSize), sf::Color::White)
            };

            window.draw(tick, 2, sf::Lines);
        }

        //деления по Y
        for (int y = 0; y <= window.getSize().y; y += step) {

            sf::Vertex tick[] = {
                sf::Vertex(sf::Vector2f(centerX - tickSize, y), sf::Color::White),
                sf::Vertex(sf::Vector2f(centerX + tickSize, y), sf::Color::White)
            };

            window.draw(tick, 2, sf::Lines);
        }

        window.draw(&parabola[0], parabola.size(), sf::LineStrip);

        window.display();
    }

    return 0;
}