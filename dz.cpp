#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Coordinate System");

    float centerX = 400.f;
    float centerY = 300.f;


    sf::Vertex xAxis[] =
    {
        sf::Vertex({0.f, centerY}, sf::Color::Black),
        sf::Vertex({800.f, centerY}, sf::Color::Black)
    };


    sf::Vertex yAxis[] =
    {
        sf::Vertex({centerX, 0.f}, sf::Color::Black),
        sf::Vertex({centerX, 600.f}, sf::Color::Black)
    };

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color::White);


        window.draw(xAxis, 2, sf::PrimitiveType::Lines);
        window.draw(yAxis, 2, sf::PrimitiveType::Lines);

        window.display();
    }

    return 0;
}