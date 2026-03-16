#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

float window_size_x = 800;
float window_size_y = 600;
float scale = 50;
float center_x = window_size_x / 2;
float center_y = window_size_y / 2;

float offset = 50;

void create_dpsk(RenderWindow& window, float x, float y) {
    /*Функция строит декартову систему координат
    * RenderWindow& window - ссылка на окно для построения графика
    * float x - центр абсцисс
    * float y - центр ординат
    */
    RectangleShape ox(Vector2f(window_size_x - 2 * offset, 1));
    ox.setPosition({ offset, y });
    ox.setFillColor(Color(100, 100, 100));
    window.draw(ox);

    RectangleShape oy(Vector2f(1, window_size_y - 2  * offset));
    oy.setPosition({ x, offset });
    oy.setFillColor(Color(100, 100, 100));
    window.draw(oy);

    ConvexShape arrowX;
    arrowX.setPointCount(3);
    arrowX.setPoint(0, Vector2f(window_size_x - offset, y));
    arrowX.setPoint(1, Vector2f(window_size_x - offset - 10, y - 5));
    arrowX.setPoint(2, Vector2f(window_size_x - offset - 10, y + 5));
    arrowX.setFillColor(Color(100, 100, 100));
    window.draw(arrowX);

    ConvexShape arrowY;
    arrowY.setPointCount(3);
    arrowY.setPoint(0, Vector2f(x, offset));
    arrowY.setPoint(1, Vector2f(x - 5, offset + 10));
    arrowY.setPoint(2, Vector2f(x + 5, offset + 10));
    arrowY.setFillColor(Color(100, 100, 100));
    window.draw(arrowY);

    int min_x = int(-center_x / scale) - 1;
    int max_x = int((window_size_x - center_x) / scale) + 1;

    int min_y = int(-(center_y - offset) / scale) - 1;
    int max_y = int((window_size_y - offset - center_y) / scale) + 1;

    for (int i = min_x; i <= max_x; i++) {
        float x_pos = center_x + i * scale;
        if (x_pos > offset && x_pos < window_size_x - offset) {
            RectangleShape tick(Vector2f(1, 10));
            tick.setPosition({ x_pos, center_y - 5 });
            tick.setFillColor(Color(150, 150, 150));
            window.draw(tick);
        }
    }

    for (int j = min_y; j <= max_y; j++) {
        float y_pos = center_y - j * scale;
        if (y_pos > offset and y_pos < window_size_y - offset) {
            RectangleShape tick(Vector2f(10, 1));
            tick.setPosition({ center_x - 5, y_pos });
            tick.setFillColor(Color(150, 150, 150));
            window.draw(tick);
        }
    }

}

void draw_func(RenderWindow& window) {
    /*Функция для построения графика
    window - ссылка на окно для построения графика*/
    for (int x = 0; x < window_size_x; x++) {
        float coord_x1= x - center_x;
        float coord_y1 = center_y - (coord_x1 * coord_x1) / scale;

        float coord_x2 = (x + 1) - center_x;
        float coord_y2 = center_y - (coord_x2 * coord_x2) / scale;
            
        if (coord_y1 >= 0 and coord_y1 <= window_size_y and coord_y2 >= 0 and coord_y2 <= window_size_y) {
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

    return 0;
}


