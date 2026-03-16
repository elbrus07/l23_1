#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>

using namespace sf;
using namespace std;


float centerX = 450.0f;
float centerY = 320.0f;
float scaleFactor = 70.0f;


Vector2f convertToScreen(float x, float y) {
    return { centerX + x * scaleFactor, centerY - y * scaleFactor };
}


void drawCoordinateAxes(RenderWindow& window) {

    RectangleShape xAxis(Vector2f(window.getSize().x, 2));
    xAxis.setPosition(0, centerY);
    xAxis.setFillColor(Color(60,60,60));
    window.draw(xAxis);

    RectangleShape yAxis(Vector2f(2, window.getSize().y));
    yAxis.setPosition(centerX, 0);
    yAxis.setFillColor(Color(60,60,60));
    window.draw(yAxis);
}


void drawScale(RenderWindow& window, Font& font) {

   
    for (int i = -8; i <= 8; i++) {

        float x = centerX + i * scaleFactor;

        RectangleShape tick(Vector2f(2, 8));
        tick.setPosition(x, centerY - 4);
        tick.setFillColor(Color::Red);
        window.draw(tick);

        if (i != 0) {
            Text number;
            number.setFont(font);
            number.setString(to_string(i));
            number.setCharacterSize(14);
            number.setFillColor(Color::Black);
            number.setPosition(x - 6, centerY + 6);

            window.draw(number);
        }
    }

    
    for (int i = -5; i <= 5; i++) {

        float y = centerY - i * scaleFactor;

        RectangleShape tick(Vector2f(8, 2));
        tick.setPosition(centerX - 4, y);
        tick.setFillColor(Color::Red);
        window.draw(tick);

        if (i != 0) {
            Text number;
            number.setFont(font);
            number.setString(to_string(i));
            number.setCharacterSize(14);
            number.setFillColor(Color::Black);
            number.setPosition(centerX + 8, y - 10);

            window.draw(number);
        }
    }
}


void drawFunction(RenderWindow& window) {

    float step = 0.03f;

    for (float x = -8; x < -step; x += step) {

        float y = 1.0f / x;

        Vector2f p1 = convertToScreen(x, y);
        Vector2f p2 = convertToScreen(x + step, 1.0f / (x + step));

        Vertex line[] = {
            Vertex(p1, Color::Green),
            Vertex(p2, Color::Green)
        };

        window.draw(line, 2, Lines);
    }

    for (float x = step; x <= 8; x += step) {

        float y = 1.0f / x;

        Vector2f p1 = convertToScreen(x, y);
        Vector2f p2 = convertToScreen(x + step, 1.0f / (x + step));

        Vertex line[] = {
            Vertex(p1, Color::Green),
            Vertex(p2, Color::Green)
        };

        window.draw(line, 2, Lines);
    }
}

int main() {

    RenderWindow window(VideoMode(900, 650), "Function y = 1/x");

    Font font;
    font.loadFromFile("arial.ttf");

    while (window.isOpen()) {

        Event event;
        while (window.pollEvent(event)) {

            if (event.type == Event::Closed)
                window.close();
        }

        window.clear(Color(240,240,240));

        drawCoordinateAxes(window);
        drawScale(window, font);
        drawFunction(window);

        window.display();
    }

    return 0;
}