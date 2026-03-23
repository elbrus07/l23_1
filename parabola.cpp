#include <SFML/Graphics.hpp>
#include <vector>

int main() {
    // Настройки окна и графики
    const int W = 800;
    const int H = 600;
    sf::RenderWindow window(sf::VideoMode(W, H), "Simple Parabola");

    // Параметры системы координат
    sf::Vector2f center(W / 2.0f, H / 2.0f);
    float scale = 30.0f; // Пикселей в одной единице графика

    // 1. Создаем оси (ДПСК) - Черные
    sf::Vertex axes[] = {
        // Ось X
        sf::Vertex(sf::Vector2f(0, center.y), sf::Color::Black),
        sf::Vertex(sf::Vector2f(W, center.y), sf::Color::Black),
        // Ось Y
        sf::Vertex(sf::Vector2f(center.x, 0), sf::Color::Black),
        sf::Vertex(sf::Vector2f(center.x, H), sf::Color::Black)
    };

    // 2. Генерируем точки параболы - Красные
    // Используем VertexArray для компактности и производительности
    sf::VertexArray curve(sf::PrimitiveType::LineStrip);
    
    for (float x = -10.0f; x <= 10.0f; x += 0.1f) {
        float y = x * x; // Формула функции

        // Перевод из математических координат в экранные
        float screenX = center.x + (x * scale);
        float screenY = center.y - (y * scale); // Минус, так как Y в SFML идет вниз

        curve.append(sf::Vertex(sf::Vector2f(screenX, screenY), sf::Color::Red));
    }

    // Главный цикл
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Очистка экрана (Светло-серый фон)
        window.clear(sf::Color(200, 200, 200));

        // Рисуем оси
        window.draw(axes, 4, sf::Lines);

        // Рисуем график
        window.draw(curve);

        window.display();
    }

    return 0;
}