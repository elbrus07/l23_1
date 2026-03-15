#include <SFML/Graphics.hpp>
#include <cmath>

using namespace sf;
using namespace std;

float originX = 400.0f;
float originY = 300.0f;

// Масштаб
float zoom = 50.0f;
Vector2f mathToScreen(float mathX, float mathY) {
    return { originX + mathX * zoom, originY - mathY * zoom };
}

// Деления
void drawMarks(RenderWindow& canvas, Font& textFont) {
    // Горизонтальные деления (ось X)
    for (int val = -8; val <= 8; ++val) {
        if (val == 0) continue;

        float screenX = originX + val * zoom;
        float screenY = originY;

        RectangleShape mark(Vector2f(1, 5));
        mark.setPosition(screenX - 0.5f, screenY - 2.5f);
        mark.setFillColor(Color::Black);
        canvas.draw(mark);

    }

    // Вертикальные деления (ось Y)
    for (int val = -6; val <= 6; ++val) {
        if (val == 0) continue;

        float screenX = originX;
        float screenY = originY - val * zoom;

        RectangleShape mark(Vector2f(5, 1));
        mark.setPosition(screenX - 2.5f, screenY - 0.5f);
        mark.setFillColor(Color::Black);
        canvas.draw(mark);

    }
}

// Рисование осей координат
void drawAxes(RenderWindow& canvas) {
    // ось (X)
    RectangleShape axisX(Vector2f(canvas.getSize().x, 1));
    axisX.setPosition({ 0, originY });
    axisX.setFillColor(Color::Black);
    canvas.draw(axisX);

    // ось (Y)
    RectangleShape axisY(Vector2f(1, canvas.getSize().y));
    axisY.setPosition({ originX, 0 });
    axisY.setFillColor(Color::Black);
    canvas.draw(axisY);
}


void plotGraph(RenderWindow& canvas) {
    float step = 0.05f;

    for (float mathX = -8.0f; mathX < -step; mathX += step) {
        float mathY = 1.0f / mathX;

        Vector2f pointA = mathToScreen(mathX, mathY);
        Vector2f pointB = mathToScreen(mathX + step, 1.0f / (mathX + step));

        if (pointA.y >= 0 && pointA.y <= canvas.getSize().y &&
            pointB.y >= 0 && pointB.y <= canvas.getSize().y) {
            Vertex segment[] = {
                Vertex(pointA, Color::Blue),
                Vertex(pointB, Color::Blue)
            };
            canvas.draw(segment, 2, Lines);
        }
    }

    for (float mathX = step; mathX <= 8.0f; mathX += step) {
        float mathY = 1.0f / mathX;

        Vector2f pointA = mathToScreen(mathX, mathY);
        Vector2f pointB = mathToScreen(mathX + step, 1.0f / (mathX + step));

        if (pointA.y >= 0 && pointA.y <= canvas.getSize().y &&
            pointB.y >= 0 && pointB.y <= canvas.getSize().y) {
            Vertex segment[] = {
                Vertex(pointA, Color::Blue),
                Vertex(pointB, Color::Blue)
            };
            canvas.draw(segment, 2, Lines);
        }
    }
}

int main() {
    RenderWindow canvas(VideoMode({800, 600}), "Graph of y = 1/x");

    while (canvas.isOpen()) {
        Event ev;
        while (canvas.pollEvent(ev)) {
            if (ev.type == Event::Closed)
                canvas.close();
        }

        canvas.clear(Color::White); 

        drawAxes(canvas);
        drawMarks(canvas, textFont);
        plotGraph(canvas);

        canvas.display();
    }

    return 0;
}