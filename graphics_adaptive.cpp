#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <string>

// --- БАЗОВЫЙ КЛАСС ДЛЯ ВСЕХ ГРАФИКОВ ---
class Graph {
protected:
    sf::Color color;           // Цвет линии
    sf::VertexArray points;    // Массив точек для рисования
public:
    Graph(sf::Color c) : color(c) { 
        // Указываем, что точки нужно соединять линиями
        points.setPrimitiveType(sf::LineStrip); 
    }

    // Общая функция для расчета координат (у каждого графика своя)
    virtual void calculate(float scale, sf::Vector2f center, sf::Vector2u windowSize) = 0;
    
    // Рисуем график в окне
    void draw(sf::RenderWindow& window) { window.draw(points); }
};

// --- КОНКРЕТНЫЕ ВИДЫ ГРАФИКОВ ---

class Parabola : public Graph {
public:
    Parabola(sf::Color c) : Graph(c) {}
    void calculate(float scale, sf::Vector2f center, sf::Vector2u windowSize) override {
        points.clear();
        for (float x = -20.0f; x <= 20.0f; x += 0.1f) {
            float y = x * x; // Формула параболы
            // Переводим математику в пиксели на экране
            points.append(sf::Vertex({center.x + x * scale, center.y - y * scale}, color));
        }
    }
};

class Line : public Graph {
public:
    Line(sf::Color c) : Graph(c) {}
    void calculate(float scale, sf::Vector2f center, sf::Vector2u windowSize) override {
        points.clear();
        for (float x = -50.0f; x <= 50.0f; x += 1.0f) {
            // Формула прямой y = x
            points.append(sf::Vertex({center.x + x * scale, center.y - x * scale}, color));
        }
    }
};

class Sinusoid : public Graph {
public:
    Sinusoid(sf::Color c) : Graph(c) {}
    void calculate(float scale, sf::Vector2f center, sf::Vector2u windowSize) override {
        points.clear();
        for (float x = -50.0f; x <= 50.0f; x += 0.1f) {
            float y = std::sin(x); // Формула синуса
            points.append(sf::Vertex({center.x + x * scale, center.y - y * scale}, color));
        }
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Graph Selector Tool");
    
    sf::Font font;
    // Загружаем шрифт (убедись, что путь правильный!)
    font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");

    float scale = 40.0f; // Начальный масштаб
    
    Parabola parabola(sf::Color::Red);
    Line line(sf::Color::Blue);
    Sinusoid sinusoid(sf::Color::Green);

    // Указатель на тот график, который мы рисуем сейчас
    Graph* currentGraph = &parabola; 

    // Настройка кнопок управления (позиция и цвет)
    sf::RectangleShape btnPlus(sf::Vector2f(40, 40)); btnPlus.setPosition(20, 20); btnPlus.setFillColor(sf::Color(100,100,100));
    sf::RectangleShape btnMinus(sf::Vector2f(40, 40)); btnMinus.setPosition(70, 20); btnMinus.setFillColor(sf::Color(100,100,100));

    sf::RectangleShape selP(sf::Vector2f(120, 40)); selP.setPosition(20, 80); selP.setFillColor(sf::Color(150, 50, 50));
    sf::Text txtP("Parabola", font, 18); txtP.setPosition(30, 90);

    sf::RectangleShape selL(sf::Vector2f(120, 40)); selL.setPosition(20, 130); selL.setFillColor(sf::Color(50, 50, 150));
    sf::Text txtL("Line", font, 18); txtL.setPosition(30, 140);

    sf::RectangleShape selS(sf::Vector2f(120, 40)); selS.setPosition(20, 180); selS.setFillColor(sf::Color(50, 150, 50));
    sf::Text txtS("Sinus", font, 18); txtS.setPosition(30, 190);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            // Проверяем клики мышки по кнопкам
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f m(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
                
                // Изменение масштаба
                if (btnPlus.getGlobalBounds().contains(m)) scale += 10.0f;
                if (btnMinus.getGlobalBounds().contains(m) && scale > 5) scale -= 10.0f;

                // Выбор текущего графика
                if (selP.getGlobalBounds().contains(m)) currentGraph = &parabola;
                if (selL.getGlobalBounds().contains(m)) currentGraph = &line;
                if (selS.getGlobalBounds().contains(m)) currentGraph = &sinusoid;
            }
        }

        // Находим центр окна
        sf::Vector2f center(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
        
        // Обновляем координаты точек графика
        currentGraph->calculate(scale, center, window.getSize());

        window.clear(sf::Color(220, 220, 220)); // Очищаем экран серым

        // Рисуем оси координат (черные линии)
        sf::Vertex axes[] = {
            sf::Vertex({0, center.y}, sf::Color::Black), sf::Vertex({(float)window.getSize().x, center.y}, sf::Color::Black),
            sf::Vertex({center.x, 0}, sf::Color::Black), sf::Vertex({center.x, (float)window.getSize().y}, sf::Color::Black)
        };
        window.draw(axes, 4, sf::Lines);

        // Рисуем выбранный график
        currentGraph->draw(window);

        // Рисуем кнопки и текст поверх всего
        window.draw(btnPlus); window.draw(btnMinus);
        window.draw(selP); window.draw(selL); window.draw(selS);
        window.draw(txtP); window.draw(txtL); window.draw(txtS);

        window.display();
    }
    return 0;
}