#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>
#include <string>

using namespace sf;
using namespace std;


struct Config {
	float window_size_x = 1000;
	float window_size_y = 1000;
	string title = "Graphic";

	float scale = 50;
	float offset = 50;

	Color graphic_color = Color::White;
	function<float(float)> func = [](float x) { return x * x; };
};


class Fonts {
public:
	Fonts() {
		if (!font.loadFromFile("arial.ttf")) {
			cout << "Шрифт не загружен" << endl;
		}
		else {
			cout << "Шрифт загружен" << endl;
		}
	}

	Font& getFont() { return font; }

private:
	Font font;
};


class CoordSys {
public:
	CoordSys(const Config& cf, Font& f)
		: window_size_x(cf.window_size_x), window_size_y(cf.window_size_y),
		scale(cf.scale), offset(cf.offset),
		center_x(cf.window_size_x / 2), center_y(cf.window_size_y / 2), font(f) {
	}

	void draw(RenderWindow& window) {
		draw_axes(window);
		draw_ticks(window);

		Text label_x;
		label_x.setFont(font);
		label_x.setString("x");
		label_x.setCharacterSize(16);
		label_x.setFillColor(Color(200, 200, 200));
		label_x.setPosition(window_size_x - 20, center_y - 20);
		window.draw(label_x);

		Text label_y;
		label_y.setFont(font);
		label_y.setString("y");
		label_y.setCharacterSize(16);
		label_y.setFillColor(Color(200, 200, 200));
		label_y.setPosition(center_x + 5, 5);
		window.draw(label_y);

		if (center_x > 0 and center_x < window_size_x and center_y > 0 and center_y < window_size_y) {
			Text zero;
			zero.setFont(font);
			zero.setString("0");
			zero.setCharacterSize(13);
			zero.setFillColor(Color(200, 200, 200));
			zero.setPosition(center_x + 5, center_y + 5);
			window.draw(zero);
		}
	}

	float getCenterX() const { return center_x; }
	float getCenterY() const { return center_y; }
	float getscale() const { return scale; }
	float getoffset() const { return offset; }
	float getWinX() const { return window_size_x; }
	float getWinY() const { return window_size_y; }

	void move(float dx, float dy) {
		center_x += dx;
		center_y += dy;
	}

	void zoom(float factor) {
		scale *= factor;
		if (scale < 10) scale = 10;
		if (scale > 200) scale = 200;
	}

	void setCenterX(float x) { center_x = x; }
	void setCenterY(float y) { center_y = y; }
	void setScale(float s) { scale = s; }

private:
	float window_size_x, window_size_y, scale, offset;
	float center_x, center_y;
	Font& font;

	void draw_axes(RenderWindow& window) {
		RectangleShape ox(Vector2f(window_size_x - 2 * offset, 1));
		ox.setPosition(offset, center_y);
		ox.setFillColor(Color(100, 100, 100));
		window.draw(ox);

		RectangleShape oy(Vector2f(1, window_size_y - 2 * offset));
		oy.setPosition(center_x, offset);
		oy.setFillColor(Color(100, 100, 100));
		window.draw(oy);
	}

	void draw_ticks(RenderWindow& window) {
		int min_x = int(-center_x / scale) - 1;
		int max_x = int((window_size_x - center_x) / scale) + 1;

		int min_y = int(-(center_y - offset) / scale) - 1;
		int max_y = int((window_size_y - offset - center_y) / scale) + 1;

		for (int i = min_x; i <= max_x; i++) {
			float x_pos = center_x + i * scale;
			if (x_pos > offset && x_pos < window_size_x - offset) {
				RectangleShape tick(Vector2f(1, 10));
				tick.setPosition(x_pos, center_y - 5);
				tick.setFillColor(Color(150, 150, 150));
				window.draw(tick);

				if (i != 0) {
					Text label;
					label.setFont(font);
					label.setString(to_string(i));
					label.setCharacterSize(13);
					label.setFillColor(Color(200, 200, 200));
					FloatRect b = label.getLocalBounds();
					label.setPosition(x_pos - b.width / 2.f, center_y + 5);
					window.draw(label);
				}
			}
		}

		for (int j = min_y; j <= max_y; j++) {
			float y_pos = center_y - j * scale;
			if (y_pos > offset && y_pos < window_size_y - offset) {
				RectangleShape tick(Vector2f(10, 1));
				tick.setPosition(center_x - 5, y_pos);
				tick.setFillColor(Color(150, 150, 150));
				window.draw(tick);

				if (j != 0) {
					Text label;
					label.setFont(font);
					label.setString(to_string(j));
					label.setCharacterSize(13);
					label.setFillColor(Color(200, 200, 200));
					FloatRect b = label.getLocalBounds();
					label.setPosition(center_x + 8, y_pos - b.height / 2.f);
					window.draw(label);
				}
			}
		}
	}
};

class InteractiveGr {
public:
	InteractiveGr(CoordSys& coord_sys, float win_x, float win_y)
		: cs(coord_sys), window_size_x(win_x), window_size_y(win_y) {
		step = 0.5;
		zoom = 1.001f;
	}

	void handle_input() {
		if (Keyboard::isKeyPressed(Keyboard::Left)) cs.move(-step, 0);
		if (Keyboard::isKeyPressed(Keyboard::Right)) cs.move(step, 0);
		if (Keyboard::isKeyPressed(Keyboard::Up)) cs.move(0, step);
		if (Keyboard::isKeyPressed(Keyboard::Down)) cs.move(0, -step);
		if (Keyboard::isKeyPressed(Keyboard::Equal)) cs.zoom(zoom);
		if (Keyboard::isKeyPressed(Keyboard::Hyphen)) cs.zoom(1.0f / zoom);
		if (Keyboard::isKeyPressed(Keyboard::C)) {
			cs.setCenterX(window_size_x / 2);
			cs.setCenterY(window_size_y / 2);
			cs.setScale(50);
		}
	}

private:
	CoordSys& cs;
	float window_size_x, window_size_y;
	float step;
	float zoom;
};


class Graphic {
public:
	Graphic(const Config& cf)
		: func(cf.func), color(cf.graphic_color) {
	}

	void setFunction(function<float(float)> new_func) { func = new_func; }
	void setColor(Color new_color) { color = new_color; }

	void draw(RenderWindow& window, const CoordSys& cs) {
		float cx = cs.getCenterX();
		float cy = cs.getCenterY();
		float sc = cs.getscale();
		float of = cs.getoffset();
		float win_x = cs.getWinX();
		float win_y = cs.getWinY();

		for (int x = 0; x < (int)win_x; x++) {
			float coord_x1 = (x - cx) / sc;
			float coord_y1 = cy - func(coord_x1) * sc;

			float coord_x2 = ((x + 1) - cx) / sc;
			float coord_y2 = cy - func(coord_x2) * sc;

			if (coord_y1 >= of && coord_y1 <= win_y - of &&
				coord_y2 >= of && coord_y2 <= win_y - of) {
				Vertex line[] = {
				Vertex(Vector2f(float(x), coord_y1), Color::Green),
				Vertex(Vector2f(float(x + 1), coord_y2), Color::Green)
				};
				window.draw(line, 2, Lines);
			}
		}
	}

private:
	function<float(float)> func;
	Color color;
};


class App {
public:
	App(const Config& cf)
		: cfg(cf), cs(cf, fonts.getFont()), graph(cf),
		interactive(cs, cf.window_size_x, cf.window_size_y) {
	}

	void run() {
		RenderWindow window(
			VideoMode((unsigned)cfg.window_size_x, (unsigned)cfg.window_size_y),
			cfg.title);

		while (window.isOpen()) {
			handle_events(window);
			handle_input();
			render(window);
		}
	}

private:
	Config cfg;
	Fonts fonts;
	CoordSys cs;
	Graphic graph;
	InteractiveGr interactive;

	void handle_events(RenderWindow& window) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}
	}

	void handle_input() {
		interactive.handle_input();
	}

	void render(RenderWindow& window) {
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
	cf.func = [](float x) { return x * x; };

	App app(cf);
	app.run();
	return 0;
}