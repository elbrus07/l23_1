#include <SFML/Graphics.hpp>
#include <string>

int main() {
    // Создаем окно: размер 800x600, заголовок, стандартный стиль (с кнопкой закрытия и изменением размера)
    sf::RenderWindow window(sf::VideoMode(800, 600), "Graph with Buttons", sf::Style::Default);
    
    // Подключаем шрифт для отображения текста (чисел и знаков на кнопках)
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        // Если шрифт не найден, программа продолжит работу, но текст не отобразится
    }

    // Переыменная масштаба: определяет, сколько пикселей в одной математической единице
    float scale = 40.0f; 

    // --- НАСТРОЙКА КНОПОК ---
    
    // Кнопка "Плюс" (серый квадрат)
    sf::RectangleShape btnPlus(sf::Vector2f(40, 40));
    btnPlus.setFillColor(sf::Color(100, 100, 100));
    btnPlus.setPosition(20, 20);

    // Кнопка "Минус" (серый квадрат)
    sf::RectangleShape btnMinus(sf::Vector2f(40, 40));
    btnMinus.setFillColor(sf::Color(100, 100, 100));
    btnMinus.setPosition(70, 20);

    // Текст на кнопке "+"
    sf::Text txtPlus("+", font, 30);
    txtPlus.setPosition(30, 20);
    txtPlus.setFillColor(sf::Color::White);
    
    // Текст на кнопке "-"
    sf::Text txtMinus("-", font, 30);
    txtMinus.setPosition(82, 20);
    txtMinus.setFillColor(sf::Color::White);

    // --- ГЛАВНЫЙ ЦИКЛ ПРОГРАММЫ ---
    while (window.isOpen()) {
        sf::Event event;
        
        // Опрос событий (мышь, клавиатура, закрытие окна)
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Проверка нажатия кнопок мыши
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Получаем текущие координаты курсора относительно окна
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    
                    // Проверяем, попал ли клик в границы кнопки ПЛЮС
                    if (btnPlus.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        scale += 10.0f; // Увеличиваем масштаб
                    }
                    // Проверяем, попал ли клик в границы кнопки МИНУС
                    if (btnMinus.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        if (scale > 10.0f) scale -= 10.0f; // Уменьшаем масштаб (но не до нуля)
                    }
                }
            }
        }

        // Динамическое определение центра (нужно для масштабируемости окна)
        sf::Vector2u size = window.getSize();
        sf::Vector2f center(size.x / 2.0f, size.y / 2.0f);

        // Очистка кадра (светло-серый фон)
        window.clear(sf::Color(200, 200, 200));

        // --- 1. ОТРИСОВКА ОСЕЙ ---
        sf::Vertex axes[] = {
            sf::Vertex(sf::Vector2f(0, center.y), sf::Color::Black),      // Ось X
            sf::Vertex(sf::Vector2f(size.x, center.y), sf::Color::Black),
            sf::Vertex(sf::Vector2f(center.x, 0), sf::Color::Black),      // Ось Y
            sf::Vertex(sf::Vector2f(center.x, size.y), sf::Color::Black)
        };
        window.draw(axes, 4, sf::Lines);

        // --- 2. ОТРИСОВКА ДЕЛЕНИЙ (ТИКОВ) ---
        for (int i = -50; i <= 50; i++) {
            if (i == 0) continue; // Пропускаем начало координат

            float xPos = center.x + i * scale;
            float yPos = center.y - i * scale;

            // Рисуем вертикальные черточки на оси X
            if (xPos > 0 && xPos < size.x) {
                sf::Vertex tickX[] = {
                    sf::Vertex({xPos, center.y - 5}, sf::Color::Black),
                    sf::Vertex({xPos, center.y + 5}, sf::Color::Black)
                };
                window.draw(tickX, 2, sf::Lines);
            }

            // Рисуем горизонтальные черточки на оси Y
            if (yPos > 0 && yPos < size.y) {
                sf::Vertex tickY[] = {
                    sf::Vertex({center.x - 5, yPos}, sf::Color::Black),
                    sf::Vertex({center.x + 5, yPos}, sf::Color::Black)
                };
                window.draw(tickY, 2, sf::Lines);
            }
        }

        // --- 3. ОТРИСОВКА ГРАФИКА ПАРАБОЛЫ ---
        sf::VertexArray parabola(sf::PrimitiveType::LineStrip);
        for (float x = -20.0f; x <= 20.0f; x += 0.1f) {
            float y = x * x; // Формула функции
            
            // Превращаем математические координаты в экранные пиксели
            float screenX = center.x + x * scale;
            float screenY = center.y - y * scale;

            ыы// Добавляем точку, только если она видима в окне
            if (screenX >= 0 && screenX <= size.x && screenY >= 0 && screenY <= size.y)
                parabola.append(sf::Vertex(sf::Vector2f(screenX, screenY), sf::Color::Red));
        }
        window.draw(parabola);

        // --- 4. ОТРИСОВКА ИНТЕРФЕЙСА (КНОПКИ) ---
        // Рисуем в конце, чтобы кнопки были поверх графика
        window.draw(btnPlus);
        window.draw(btnMinus);
        window.draw(txtPlus);
        window.draw(txtMinus);

        // Отображение всего нарисованного на экран
        window.display();
    }

    return 0;
}