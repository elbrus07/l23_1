#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Car");

    
    sf::RectangleShape body(sf::Vector2f(200, 50));
    body.setFillColor(sf::Color::Red);
    body.setPosition(300, 350);

    
    sf::ConvexShape roof;
    roof.setPointCount(4);
    roof.setPoint(0, sf::Vector2f(0, 50));
    roof.setPoint(1, sf::Vector2f(40, 0));
    roof.setPoint(2, sf::Vector2f(120, 0));
    roof.setPoint(3, sf::Vector2f(160, 50));
    roof.setFillColor(sf::Color::Red);
    roof.setPosition(320, 300);

    
    sf::CircleShape wheel1(25);
    wheel1.setFillColor(sf::Color::Black);
    wheel1.setPosition(330, 380);

    sf::CircleShape wheel2(25);
    wheel2.setFillColor(sf::Color::Black);
    wheel2.setPosition(450, 380);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        window.draw(body);
        window.draw(roof);
        window.draw(wheel1);
        window.draw(wheel2);

        window.display();
    }

    return 0;
}