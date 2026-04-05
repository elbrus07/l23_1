#include <SFML/Graphics.hpp>
#include <cmath>
#include <functional>
#include <sstream>


using namespace sf;

class CoordinateSystem
{
private:
	float scale = 50.f;
	Vector2f center;

public:
	CoordinateSystem(float width, float height)
	{
		center = { width / 2.f, height / 2.f };
	}

	void zoom(float delta)
	{
		scale += delta * 5.f;

		if (scale < 10.f) scale = 10.f;
		if (scale > 200.f) scale = 200.f;
	}

	Vector2f toScreen(float x, float y)
	{
		return {
			center.x + x * scale,
			center.y - y * scale
		};
	}

	void drawAxis(RenderWindow& window)
	{
		Vertex xAxis[] =
		{
			Vertex({0.f, center.y}, Color::White),
			Vertex({(float)window.getSize().x, center.y}, Color::Black)
		};

		Vertex yAxis[] =
		{
			Vertex({center.x, 0.f}, Color::White),
			Vertex({center.x, (float)window.getSize().y}, Color::Black)
		};

		window.draw(xAxis, 2, Lines);
		window.draw(yAxis, 2, Lines);
	}

	void drawTicks(RenderWindow& window)
	{
		float width = (float)window.getSize().x;
		float height = (float)window.getSize().y;

		for (float x = center.x; x < width; x += scale)
		{
			Vertex tick[] =
			{
				Vertex({x, center.y - 5.f}, Color::Black),
				Vertex({x, center.y + 5.f}, Color::Black)
			};
			window.draw(tick, 2, Lines);
		}

		for (float x = center.x; x > 0.f; x -= scale)
		{
			Vertex tick[] =
			{
				Vertex({x, center.y - 5.f}, Color::Black),
				Vertex({x, center.y + 5.f}, Color::Black)
			};
			window.draw(tick, 2, Lines);
		}

		for (float y = center.y; y < height; y += scale)
		{
			Vertex tick[] =
			{
				Vertex({center.x - 5.f, y}, Color::Black),
				Vertex({center.x + 5.f, y}, Color::Black)
			};
			window.draw(tick, 2, Lines);
		}

		for (float y = center.y; y > 0.f; y -= scale)
		{
			Vertex tick[] =
			{
				Vertex({center.x - 5.f, y}, Color::Black),
				Vertex({center.x + 5.f, y}, Color::Black)
			};
			window.draw(tick, 2, Lines);
		}
	}

	void drawArrows(RenderWindow& window)
	{
		float size = 10.f;

		ConvexShape arrowX;
		arrowX.setPointCount(3);
		arrowX.setPoint(0, { (float)window.getSize().x - size, center.y - size / 2.f });
		arrowX.setPoint(1, { (float)window.getSize().x, center.y });
		arrowX.setPoint(2, { (float)window.getSize().x - size, center.y + size / 2.f });
		arrowX.setFillColor(Color::Black);

		ConvexShape arrowY;
		arrowY.setPointCount(3);
		arrowY.setPoint(0, { center.x - size / 2.f, size });
		arrowY.setPoint(1, { center.x, 0.f });
		arrowY.setPoint(2, { center.x + size / 2.f, size });
		arrowY.setFillColor(Color::Black);

		window.draw(arrowX);
		window.draw(arrowY);
	}
	void drawGraph(RenderWindow& window, std::function<float(float)> func, Color color = Color::Blue, float step = 0.05f)
	{
		float width = (float)window.getSize().x;	
		float height = (float)window.getSize().y;

		// Определяем видимый диапазон по X в мировых координатах
		float xMin = (0 - center.x) / scale;
		float xMax = (width - center.x) / scale;

		// Если диапазон вырожден, ничего не рисуем
		if (xMin >= xMax) return;

		VertexArray points(LinesStrip);
		for (float x = xMin; x <= xMax; x += step)
		{
			float y = func(x);
			Vector2f screenPos = toScreen(x, y);
			// Отсечение по экрану: если точка сильно вне экрана, можно пропускать,
			// но для простоты добавляем все, линия может уходить за край
			if (screenPos.x >= 0 && screenPos.x <= width && screenPos.y >= 0 && screenPos.y <= height)
			{
				points.append(Vertex(screenPos, color));
			}
			else
			{
				// Если точка вне экрана, разрываем линию, добавляя точку с таким же цветом,
				// но потом следующий сегмент начнётся заново (LinesStrip автоматически не разрывает).
				// Чтобы разорвать, нужно начать новый массив. Здесь упростим: просто не добавляем
				// и продолжаем. Линия может быть некорректной на границе, но для демонстрации достаточно.
				// Более правильное решение: разбивать на отрезки, но для простоты оставим так.
			}
		}
		window.draw(points);
	}

	void draw(RenderWindow& window)
	{
		drawAxis(window);
		drawTicks(window);
		drawArrows(window);
	}
};
float f1(float x)
{
	return std::sin(x);
}

float f2(float x)
{
	return 0.2f * x * x - 1.5f;
}

int main()
{
	RenderWindow window(VideoMode(800, 600), "graph");

	CoordinateSystem coord(800.f, 600.f);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::MouseWheelScrolled)
				coord.zoom(event.mouseWheelScroll.delta);
		}

		window.clear(Color::White);
		coord.draw(window);
		coord.drawGraph(window, f1, Color::Blue, 0.05f);
		coord.drawGraph(window, f2, Color::Red, 0.05f);
		window.display();
	}

	return 0;
}