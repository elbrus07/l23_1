#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <string>
class Grafik
{
private:
    sf::RenderWindow window;
    int width = 800;
    int height = 600;
    float scale = 40.f;
    sf::Font font;

public:
    Grafik()
    {
        window.create(sf::VideoMode(width, height), "grafik");
        font.loadFromFile("arial.ttf");
    }
    void run()
    {
        while (window.isOpen())
        {
            handleEvents();
            render();
        }
    }

private:
    void handleEvents()
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            // масштаб
            if (event.type == sf::Event::MouseWheelScrolled)
            {
                if (event.mouseWheelScroll.delta > 0)
                    scale += 5.f;
                else
                    scale -= 5.f;
                if (scale < 10.f)
                    scale = 10.f;
            }
        }
    }
    void drawAxes()
    {
        // X
        sf::Vertex xAxis[] =
            {
                sf::Vertex(sf::Vector2f(0, height / 2.f), sf::Color::Black),
                sf::Vertex(sf::Vector2f(width, height / 2.f), sf::Color::Black)};
        // Y
        sf::Vertex yAxis[] =
            {
                sf::Vertex(sf::Vector2f(width / 2.f, 0), sf::Color::Black),
                sf::Vertex(sf::Vector2f(width / 2.f, height), sf::Color::Black)};
        window.draw(xAxis, 2, sf::Lines);
        window.draw(yAxis, 2, sf::Lines);
    }
    void drawLabels()
    {
        for (int i = -10; i <= 10; i++)
        {
            // X
            sf::Text text;
            text.setFont(font);
            text.setCharacterSize(14);
            text.setFillColor(sf::Color::Black);
            text.setString(std::to_string(i));
            float x = width / 2.f + i * scale;
            text.setPosition(x - 10, height / 2.f + 5);
            window.draw(text);
            // Y
            sf::Text textY;
            textY.setFont(font);
            textY.setCharacterSize(14);
            textY.setFillColor(sf::Color::Black);
            textY.setString(std::to_string(i));
            float y = height / 2.f - i * scale;
            textY.setPosition(width / 2.f + 5, y - 10);
            window.draw(textY);
        }
    }
    void drawGraph()
    {
        sf::VertexArray graph(sf::LineStrip);
        for (float x = -10; x <= 10; x += 0.01f)
        {
            float y = std::sin(x);
            float sx = width / 2.f + x * scale;
            float sy = height / 2.f - y * scale;
            graph.append(sf::Vertex(sf::Vector2f(sx, sy), sf::Color::Green));
        }
        window.draw(graph);
    }
    void render()
    {
        window.clear(sf::Color::White);
        drawAxes();
        drawLabels();
        drawGraph();
        window.display();
    }
};
int main()
{
    Grafik app;
    app.run();
    return 0;
}
