#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <string>

// оформлление кнопок
struct Button {
    sf::RectangleShape shape;
    sf::Text text;

    Button(sf::Vector2f pos, sf::Vector2f size, sf::Color color, std::string label, sf::Font& font) {
        shape.setPosition(pos);
        shape.setSize(size);
        shape.setFillColor(color);
        shape.setOutlineThickness(2);
        shape.setOutlineColor(sf::Color::White); // Белая рамка, чтобы кнопка выделялась

        text.setFont(font);
        text.setString(label);
        text.setCharacterSize(16);
        text.setFillColor(sf::Color::White);
        
        // Центрируем текст внутри кнопки
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        text.setPosition(pos.x + size.x / 2.0f, pos.y + size.y / 2.0f);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
        window.draw(text);
    }
};

//Базовый класс для всех графиков
class Graph {
protected:
    sf::Color color;
    sf::VertexArray points;
public:
    Graph(sf::Color c) : color(c) { points.setPrimitiveType(sf::LineStrip); }
    virtual void calculate(float scale, sf::Vector2f center) = 0;
    void draw(sf::RenderWindow& window) { window.draw(points); }
};

class Parabola : public Graph {
public:
    Parabola(sf::Color c) : Graph(c) {}
    void calculate(float scale, sf::Vector2f center) override {
        points.clear();
        for (float x = -30.0f; x <= 30.0f; x += 0.1f) {
            float y = x * x;
            points.append(sf::Vertex({center.x + x * scale, center.y - y * scale}, color));
        }
    }
};

class Line : public Graph {
public:
    Line(sf::Color c) : Graph(c) {}
    void calculate(float scale, sf::Vector2f center) override {
        points.clear();
        for (float x = -50.0f; x <= 50.0f; x += 0.5f) {
            points.append(sf::Vertex({center.x + x * scale, center.y - x * scale}, color));
        }
    }
};

class Sinusoid : public Graph {
public:
    Sinusoid(sf::Color c) : Graph(c) {}
    void calculate(float scale, sf::Vector2f center) override {
        points.clear();
        for (float x = -50.0f; x <= 50.0f; x += 0.1f) {
            float y = std::sin(x);
            points.append(sf::Vertex({center.x + x * scale, center.y - y * scale}, color));
        }
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Graph Visualizer");
    
    sf::Font font;
    // Если путь к шрифту не сработает
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) return -1;

    float scale = 40.0f;
    
    Parabola parabola(sf::Color(255, 100, 100));
    Line line(sf::Color(100, 100, 255));
    Sinusoid sinusoid(sf::Color(100, 255, 100));

    Graph* currentGraph = &parabola;

    // Создаем кнопки 
    Button btnPlus({20, 20}, {40, 40}, sf::Color(80, 80, 80), "+", font);
    Button btnMinus({70, 20}, {40, 40}, sf::Color(80, 80, 80), "-", font);
    Button selP({20, 80}, {120, 40}, sf::Color(180, 50, 50), "Parabola", font);
    Button selL({20, 130}, {120, 40}, sf::Color(50, 50, 180), "Line", font);
    Button selS({20, 180}, {120, 40}, sf::Color(50, 180, 50), "Sinus", font);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f m(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
                
                if (btnPlus.shape.getGlobalBounds().contains(m)) scale += 5.0f;
                if (btnMinus.shape.getGlobalBounds().contains(m) && scale > 10) scale -= 5.0f;
                if (selP.shape.getGlobalBounds().contains(m)) currentGraph = &parabola;
                if (selL.shape.getGlobalBounds().contains(m)) currentGraph = &line;
                if (selS.shape.getGlobalBounds().contains(m)) currentGraph = &sinusoid;
            }
        }

        sf::Vector2f center(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
        currentGraph->calculate(scale, center);

        window.clear(sf::Color(240, 240, 240));

        // Рисование сетки
        sf::VertexArray grid(sf::Lines);
        for (int i = -50; i <= 50; ++i) {
            float x = center.x + i * scale;
            float y = center.y + i * scale;
            
            // Вертикальная линия сетки
            grid.append(sf::Vertex({x, 0.0f}, sf::Color(200, 200, 200)));
            grid.append(sf::Vertex({x, (float)window.getSize().y}, sf::Color(200, 200, 200)));
            // Горизонтальная линия сетки
            grid.append(sf::Vertex({0.0f, y}, sf::Color(200, 200, 200)));
            grid.append(sf::Vertex({(float)window.getSize().x, y}, sf::Color(200, 200, 200)));
        }
        window.draw(grid);

        // Оси координат 
        sf::Vertex axes[] = {
            sf::Vertex({0, center.y}, sf::Color::Black), sf::Vertex({(float)window.getSize().x, center.y}, sf::Color::Black),
            sf::Vertex({center.x, 0}, sf::Color::Black), sf::Vertex({center.x, (float)window.getSize().y}, sf::Color::Black)
        };
        window.draw(axes, 4, sf::Lines);

        currentGraph->draw(window);

        // Отрисовка кнопок
        btnPlus.draw(window);
        btnMinus.draw(window);
        selP.draw(window);
        selL.draw(window);
        selS.draw(window);

        window.display();
    }
    return 0;
}