#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>  
#include <functional>

using namespace sf;
using namespace std;

/*
class InteractiveGr {
public:
    InteractiveGr(float center_x, float center_y, float scale)
        : center_x(center_x), center_y(center_y), scale(scale) {}

    void handle_input() {
        if (Keyboard::isKeyPressed(Keyboard::Key::Left)) center_x += step
    }
};
*/

struct Config {
    /*Класс для работы с графиком*/
    float window_size_x = 1000;
    float window_size_y = 1000;
    string title = "Graphic";

    float scale = 50;
    float offset = 50;

    Color graphic_color = Color::White;
    function<float(float)> func = [](float x) { return x * x; };
};
/*
class Fonts {
public:
    Fonts() {
        filesystem::path path = "C:\\Users\\1\\source\\repos\\sfml_new\\x64\\Debug\\BRLNSR.TTF";
        if (!font.openFromFile(path)) {
            cout << "Шрифт не загружен" << endl;
        }
        else {
            cout << "Шрифт загружен" << endl;
        }
    }

    Font& getFont() {return font;}

private:
    Font font;
};
*/
class CoordSys {
    /*Класс дл построения декартовой системы координат*/
public:
    CoordSys(const Config& cf)
        : window_size_x(cf.window_size_x), window_size_y(cf.window_size_y), scale(cf.scale),
          offset(cf.offset), center_x(cf.window_size_x / 2), center_y(cf.window_size_y / 2) {}
    
    void draw(RenderWindow& window) {
        draw_axes(window);
        draw_arrows(window);
        draw_ticks(window);
    }

    float getCenterX() const{ return center_x; }
    float getCenterY() const{ return center_y; }
    float getscale() const{ return scale; }
    float getoffset() const { return offset; }
    float getWinX() const{ return window_size_x; }
    float getWinY() const{ return window_size_y; }

private:
    float window_size_x, window_size_y, scale, offset;
    float center_x, center_y;

    void draw_axes(RenderWindow& window) {
        /*Строит оси декартовой системы координат*/
        RectangleShape ox(Vector2f(window_size_x - 2 * offset, 1));
        ox.setPosition({ offset, center_y });
        ox.setFillColor(Color(100, 100, 100));
        window.draw(ox);

        RectangleShape oy(Vector2f(1, window_size_y - 2  * offset));
        oy.setPosition({ center_x, offset });
        oy.setFillColor(Color(100, 100, 100));
        window.draw(oy);
    }

    void draw_arrows(RenderWindow& window) {
        /*Рисует стрелки для указания направления осей*/
        ConvexShape arrowX;
        arrowX.setPointCount(3);
        arrowX.setPoint(0, Vector2f(window_size_x - offset, center_y));
        arrowX.setPoint(1, Vector2f(window_size_x - offset - 10, center_y - 5));
        arrowX.setPoint(2, Vector2f(window_size_x - offset - 10, center_y + 5));
        arrowX.setFillColor(Color(100, 100, 100));
        window.draw(arrowX);

        ConvexShape arrowY;
        arrowY.setPointCount(3);
        arrowY.setPoint(0, Vector2f(center_x, offset));
        arrowY.setPoint(1, Vector2f(center_x - 5, offset + 10));
        arrowY.setPoint(2, Vector2f(center_x + 5, offset + 10));
        arrowY.setFillColor(Color(100, 100, 100));
        window.draw(arrowY);
    }

    void draw_ticks(RenderWindow& window) {
        /*Строит штрихи на осях*/
        int min_x = int(-center_x / scale) - 1;
        int max_x = int((window_size_x - center_x) / scale) + 1;

        int min_y = int(-(center_y - offset) / scale) - 1;
        int max_y = int((window_size_y - offset - center_y) / scale) + 1;

        for (int i = min_x; i <= max_x; i++) {
            float x_pos = center_x + i * scale;
            if (x_pos > offset and x_pos < window_size_x - offset) {
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


};

class Graphic {
    /*Класс для построения графика*/
public:
    Graphic(const Config& cf)
        :func(cf.func), color(cf.graphic_color){}

    void setFunction(function<float(float)> new_func) {func = new_func;}
    void setColor(Color new_color) {color = new_color;}

    void draw(RenderWindow& window, const CoordSys& cs) {
        float cx = cs.getCenterX();
        float cy = cs.getCenterY();
        float sc = cs.getscale();
        float of = cs.getoffset();
        float window_size_x = cs.getWinX();
        float window_size_y = cs.getWinY();

        for (int x = 0; x < window_size_x; x++) {
            float coord_x1 = (x - cx) / sc;
            float coord_y1 = cy - func(coord_x1) * sc;

            float coord_x2 = ((x + 1) - cx) / sc;
            float coord_y2 = cy - func(coord_x2) * sc;

            if (coord_y1 >= of and coord_y1 <= window_size_y - of and coord_y2 >= of and coord_y2 <= window_size_y - of) {
                Vertex line[] = {
                    Vertex(Vector2f(float(x), coord_y1), Color::Green),
                    Vertex(Vector2f(float(x + 1), coord_y2), Color::Green)
                };
                window.draw(line, 2, PrimitiveType::Lines);
            }
        }
    }

private:
    function<float(float)> func;
    Color color;
};

class App {
    /*Главный класс. Управляет окном*/
public:
    App(const Config& cf)
        : cfg(cf), cs(cf), graph(cf) {}

    void run() {
        /*Запускает главный цикл*/
        RenderWindow window(
            VideoMode({ (unsigned)cfg.window_size_x, (unsigned)cfg.window_size_y }),
            "Graphic");
        while (window.isOpen()) {
            handle_events(window);
            render(window);
        }
    }

private:
    Config cfg;
    CoordSys cs;
    Graphic graph;
    //Fonts font;

    void handle_events(RenderWindow& window) {
        /*Обрабатывает события окна*/
        while (const optional event = window.pollEvent()) {
            if (event->is<Event::Closed>())
                window.close();
        }
    }

    void render(RenderWindow& window) {
        /*Очищает экран и отрисовывает все объекты*/
        window.clear(Color::Black);
        cs.draw(window);
        graph.draw(window, cs);
        window.display();
    }
};

int main() {

    Config cf;
    cf.window_size_x = 800;
    cf.window_size_y = 600;
    cf.title = "Graphic";
    cf.scale = 50;
    cf.offset = 50;
    cf.graphic_color = Color::Green;
    cf.func = [](float x) { return x;};

    App app(cf);
    app.run();
    return 0;
}