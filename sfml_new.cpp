#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

    float center_x = 400;
    float center_y = 300;
    float scale = 50;

void create_dpsk(RenderWindow& window, float x, float y) {
    /*Функция строит декартову систему координат
    * RenderWindow& window - ссылка на окно для построения графика
    * float x - центр абсцисс
    * float y - центр ординат
    */
    RectangleShape ox(Vector2f(800, 1));
    ox.setPosition({ 0, y });
    ox.setFillColor(Color(100, 100, 100));
    window.draw(ox);

    RectangleShape oy(Vector2f(1, 600));
    oy.setPosition({ x, 0 });
    oy.setFillColor(Color(100, 100, 100));
    window.draw(oy);
}

void draw_func(RenderWindow& window) {
    /*Функция для построения графика
    window - ссылка на окно для построения графика*/
    for (int x = 0; x < 799; x++) {
        float coord_x1= x - center_x;
        float coord_y1 = center_y - (coord_x1 * coord_x1) / scale;

        float coord_x2 = (x + 1) - center_x;
        float coord_y2 = center_y - (coord_x2 * coord_x2) / scale;
            
        if (coord_y1 >= 0 and coord_y1 <= 600 and coord_y2 >= 0 and coord_y2 <= 600) {
            Vertex line[] = {
                Vertex(Vector2f(float(x), coord_y1), Color::Green),
                Vertex(Vector2f(float(x + 1), coord_y2), Color::Green)
            };
            window.draw(line, 2, PrimitiveType::Lines);
        }
    }
}

int main() {
    RenderWindow window(VideoMode({800, 600}), "График x^2");

    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(Color::Black);

        create_dpsk(window, center_x, center_y);
        draw_func(window);

        window.display();
    }

    /*
    while (window.isOpen())
    {
        while (const optional event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
                window.close();
        }

        window.clear(Color::Black);

        create_dpsk(window, center_x, center_y);
        draw_func(window);

        window.display();
    }
    */
    return 0;
}


