#include <SFML/Graphics.hpp>
#include <cmath>
#include <sstream>
#include <vector>

double f(double x)
{
    return std::sin(x);
}

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({1400, 900}),
        "Function Plot",
        sf::Style::Default
    );

    window.setFramerateLimit(144);

    sf::Font font;
    if (!font.openFromFile("arial.ttf"))
        return 1;

    float scale = 80.f;
    sf::Vector2f offset(700.f, 450.f);

    while (window.isOpen())
    {
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (const auto* wheel = event->getIf<sf::Event::MouseWheelScrolled>())
            {
                if (wheel->delta > 0)
                    scale *= 1.1f;
                else
                    scale /= 1.1f;

                if (scale < 5.f)
                    scale = 5.f;
            }
        }

        float speed = 8.f;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
            offset.x += speed;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
            offset.x -= speed;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
            offset.y += speed;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
            offset.y -= speed;

        window.clear(sf::Color(20, 20, 20));

        sf::VertexArray grid(sf::PrimitiveType::Lines);
        sf::VertexArray axes(sf::PrimitiveType::Lines);

        const auto size = window.getSize();

        int leftWorld =
            static_cast<int>(std::floor((-offset.x) / scale)) - 2;

        int rightWorld =
            static_cast<int>(std::ceil((size.x - offset.x) / scale)) + 2;

        int bottomWorld =
            static_cast<int>(std::floor((offset.y - size.y) / scale)) - 2;

        int topWorld =
            static_cast<int>(std::ceil(offset.y / scale)) + 2;

        for (int x = leftWorld; x <= rightWorld; x++)
        {
            float sx = offset.x + x * scale;

            grid.append(
                sf::Vertex(
                    {sx, 0.f},
                    sf::Color(50, 50, 50)
                )
            );

            grid.append(
                sf::Vertex(
                    {sx, static_cast<float>(size.y)},
                    sf::Color(50, 50, 50)
                )
            );
        }

        for (int y = bottomWorld; y <= topWorld; y++)
        {
            float sy = offset.y - y * scale;

            grid.append(
                sf::Vertex(
                    {0.f, sy},
                    sf::Color(50, 50, 50)
                )
            );

            grid.append(
                sf::Vertex(
                    {static_cast<float>(size.x), sy},
                    sf::Color(50, 50, 50)
                )
            );
        }

        axes.append(
            sf::Vertex(
                {0.f, offset.y},
                sf::Color::White
            )
        );

        axes.append(
            sf::Vertex(
                {static_cast<float>(size.x), offset.y},
                sf::Color::White
            )
        );

        axes.append(
            sf::Vertex(
                {offset.x, 0.f},
                sf::Color::White
            )
        );

        axes.append(
            sf::Vertex(
                {offset.x, static_cast<float>(size.y)},
                sf::Color::White
            )
        );

        window.draw(grid);
        window.draw(axes);

        for (int x = leftWorld; x <= rightWorld; x++)
        {
            if (x == 0)
                continue;

            float sx = offset.x + x * scale;

            sf::Text text(font);
            text.setCharacterSize(14);
            text.setString(std::to_string(x));
            text.setFillColor(sf::Color::White);
            text.setPosition({sx + 2.f, offset.y + 2.f});

            window.draw(text);
        }

        for (int y = bottomWorld; y <= topWorld; y++)
        {
            if (y == 0)
                continue;

            float sy = offset.y - y * scale;

            sf::Text text(font);
            text.setCharacterSize(14);
            text.setString(std::to_string(y));
            text.setFillColor(sf::Color::White);
            text.setPosition({offset.x + 4.f, sy - 10.f});

            window.draw(text);
        }

        sf::VertexArray graph(sf::PrimitiveType::LineStrip);

        for (unsigned int px = 0; px < size.x; px++)
        {
            double worldX = (px - offset.x) / scale;
            double worldY = f(worldX);

            float screenY =
                offset.y - static_cast<float>(worldY * scale);

            graph.append(
                sf::Vertex(
                    {
                        static_cast<float>(px),
                        screenY
                    },
                    sf::Color::Green
                )
            );
        }

        window.draw(graph);
        window.display();
    }

    return 0;
}