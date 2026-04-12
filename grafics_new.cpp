#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

class Graph {
protected:
    sf::Color color;
    sf::VertexArray points{sf::LineStrip};
public:
    Graph(sf::Color c) : color(c) {}
    virtual void calculate(float scale, sf::Vector2f center, sf::Vector2u windowSize) = 0;
    void draw(sf::RenderWindow& w) { w.draw(points); }
};

class Parabola : public Graph {
public:
    Parabola(sf::Color c) : Graph(c) {}
    void calculate(float scale, sf::Vector2f center, sf::Vector2u windowSize) override {
        points.clear();
        for (float x = -20; x <= 20; x += 0.1f)
            points.append({{center.x + x * scale, center.y - x*x * scale}, color});
    }
};

class Line : public Graph {
public:
    Line(sf::Color c) : Graph(c) {}
    void calculate(float scale, sf::Vector2f center, sf::Vector2u windowSize) override {
        points.clear();
        for (float x = -50; x <= 50; x += 1)
            points.append({{center.x + x * scale, center.y - x * scale}, color});
    }
};

class Sinusoid : public Graph {
public:
    Sinusoid(sf::Color c) : Graph(c) {}
    void calculate(float scale, sf::Vector2f center, sf::Vector2u windowSize) override {
        points.clear();
        for (float x = -50; x <= 50; x += 0.1f)
            points.append({{center.x + x * scale, center.y - std::sin(x) * scale}, color});
    }
};

class Grafik {
private:
    sf::RenderWindow window;
    int width = 800;
    int height = 600;
    float scale = 40.f;
    sf::Font font;
    
    Parabola parabola{sf::Color(255, 50, 50)};
    Line line{sf::Color(50, 150, 255)};
    Sinusoid sinusoid{sf::Color(50, 255, 50)};
    Graph* currentGraph = &parabola;
    
    // Кнопки выбора графика
    sf::RectangleShape btnParabola;
    sf::RectangleShape btnLine;
    sf::RectangleShape btnSinusoid;
    sf::Text txtParabola;
    sf::Text txtLine;
    sf::Text txtSinusoid;
    sf::Text scaleText;
    
    void setupUI() {
        // Загрузка шрифта
        std::vector<std::string> fontPaths = {
            "arial.ttf",                                    // локально
            "C:/Windows/Fonts/arial.ttf",                  // Windows
            "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", // Linux
        };
        
        bool fontLoaded = false;
        for (const auto& path : fontPaths) {
            if (font.loadFromFile(path)) {
                fontLoaded = true;
                break;
            }
        }
        
        if (!fontLoaded) {
            // Если шрифт не загрузился, продолжаем без текста на кнопках
            // (но текст всё равно будет пытаться отображаться)
        }
        
        // Кнопка Parabola
        btnParabola.setSize({130, 40});
        btnParabola.setPosition(20, 20);
        btnParabola.setFillColor(sf::Color(200, 50, 50));
        btnParabola.setOutlineColor(sf::Color::White);
        btnParabola.setOutlineThickness(2);
        
        txtParabola.setFont(font);
        txtParabola.setString("Parabola");
        txtParabola.setCharacterSize(16);
        txtParabola.setFillColor(sf::Color::White);
        txtParabola.setPosition(30, 30);
        
        // Кнопка Line
        btnLine.setSize({130, 40});
        btnLine.setPosition(20, 70);
        btnLine.setFillColor(sf::Color(50, 120, 200));
        btnLine.setOutlineColor(sf::Color::White);
        btnLine.setOutlineThickness(2);
        
        txtLine.setFont(font);
        txtLine.setString("Line");
        txtLine.setCharacterSize(16);
        txtLine.setFillColor(sf::Color::White);
        txtLine.setPosition(30, 80);
        
        // Кнопка Sinusoid
        btnSinusoid.setSize({130, 40});
        btnSinusoid.setPosition(20, 120);
        btnSinusoid.setFillColor(sf::Color(50, 180, 50));
        btnSinusoid.setOutlineColor(sf::Color::White);
        btnSinusoid.setOutlineThickness(2);
        
        txtSinusoid.setFont(font);
        txtSinusoid.setString("Sinus");
        txtSinusoid.setCharacterSize(16);
        txtSinusoid.setFillColor(sf::Color::White);
        txtSinusoid.setPosition(30, 130);
        
        // Текст масштаба
        scaleText.setFont(font);
        scaleText.setCharacterSize(14);
        scaleText.setFillColor(sf::Color(100, 100, 100));
        scaleText.setPosition(20, 180);
    }

public:
    Grafik() {
        window.create(sf::VideoMode(width, height), "Graph Selector");
        setupUI();
    }
    
    void run() {
        while (window.isOpen()) {
            handleEvents();
            render();
        }
    }

private:
    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            
            // Масштабирование колесиком мыши
            if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.delta > 0)
                    scale += 5.f;
                else
                    scale -= 5.f;
                if (scale < 10.f)
                    scale = 10.f;
                if (scale > 200.f)
                    scale = 200.f;
            }
            
            // Выбор графика по клику на кнопку
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
                
                if (btnParabola.getGlobalBounds().contains(mousePos))
                    currentGraph = &parabola;
                if (btnLine.getGlobalBounds().contains(mousePos))
                    currentGraph = &line;
                if (btnSinusoid.getGlobalBounds().contains(mousePos))
                    currentGraph = &sinusoid;
            }
        }
    }
    
    void drawAxes() {
        sf::Vector2f center(width / 2.f, height / 2.f);
        
        // Ось X
        sf::Vertex xAxis[] = {
            sf::Vertex(sf::Vector2f(0, center.y), sf::Color::Black),
            sf::Vertex(sf::Vector2f(width, center.y), sf::Color::Black)
        };
        // Ось Y
        sf::Vertex yAxis[] = {
            sf::Vertex(sf::Vector2f(center.x, 0), sf::Color::Black),
            sf::Vertex(sf::Vector2f(center.x, height), sf::Color::Black)
        };
        
        window.draw(xAxis, 2, sf::Lines);
        window.draw(yAxis, 2, sf::Lines);
    }
    
    void drawGrid() {
        sf::Vector2f center(width / 2.f, height / 2.f);
        sf::Color gridColor(200, 200, 200);
        
        // Вертикальные линии сетки
        for (int i = -10; i <= 10; i++) {
            float x = center.x + i * scale;
            if (x >= 0 && x <= width) {
                sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(x, 0), gridColor),
                    sf::Vertex(sf::Vector2f(x, height), gridColor)
                };
                window.draw(line, 2, sf::Lines);
            }
        }
        
        // Горизонтальные линии сетки
        for (int i = -10; i <= 10; i++) {
            float y = center.y - i * scale;
            if (y >= 0 && y <= height) {
                sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(0, y), gridColor),
                    sf::Vertex(sf::Vector2f(width, y), gridColor)
                };
                window.draw(line, 2, sf::Lines);
            }
        }
    }
    
    void drawLabels() {
        sf::Vector2f center(width / 2.f, height / 2.f);
        
        for (int i = -10; i <= 10; i++) {
            if (i == 0) continue; // 0 подписываем отдельно
            
            // Метки на оси X
            float x = center.x + i * scale;
            if (x >= 0 && x <= width) {
                sf::Text text;
                text.setFont(font);
                text.setCharacterSize(12);
                text.setFillColor(sf::Color(80, 80, 80));
                text.setString(std::to_string(i));
                text.setPosition(x - 5, center.y + 5);
                window.draw(text);
            }
            
            // Метки на оси Y
            float y = center.y - i * scale;
            if (y >= 0 && y <= height) {
                sf::Text text;
                text.setFont(font);
                text.setCharacterSize(12);
                text.setFillColor(sf::Color(80, 80, 80));
                text.setString(std::to_string(i));
                text.setPosition(center.x + 5, y - 8);
                window.draw(text);
            }
        }
        
        // Подпись нуля
        sf::Text zero;
        zero.setFont(font);
        zero.setCharacterSize(14);
        zero.setFillColor(sf::Color::Black);
        zero.setString("0");
        zero.setPosition(center.x + 5, center.y + 5);
        window.draw(zero);
    }
    
    void render() {
        sf::Vector2f center(width / 2.f, height / 2.f);
        sf::Vector2u windowSize(width, height);
        
        // Обновляем текущий график
        currentGraph->calculate(scale, center, windowSize);
        
        window.clear(sf::Color(245, 245, 245)); 
        
        drawGrid();      // Сетка
        drawAxes();      // Оси координат
        drawLabels();    // Цифры на осях
        
        // Рисуем график
        currentGraph->draw(window);
        
        // Рисуем UI поверх графика
        window.draw(btnParabola);
        window.draw(btnLine);
        window.draw(btnSinusoid);
        window.draw(txtParabola);
        window.draw(txtLine);
        window.draw(txtSinusoid);
        
        // Отображаем текущий масштаб
        std::stringstream ss;
        ss << "Scale: " << std::fixed << std::setprecision(0) << scale;
        scaleText.setString(ss.str());
        window.draw(scaleText);
        
        window.display();
    }
};

int main() {
    Grafik app;
    app.run();
    return 0;
}