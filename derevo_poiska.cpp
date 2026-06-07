#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

//класс узел дерева
struct Node {
    int value;
    Node *left, *right;
    
    Node(int val) : value(val), left(nullptr), right(nullptr) {}
};

// класс логика дерева
class BST {
private:
    Node* root;

    Node* insert(Node* node, int val) {
        if (!node) return new Node(val);
        if (val < node->value) node->left = insert(node->left, val);
        else if (val > node->value) node->right = insert(node->right, val);
        return node;
    }

    Node* remove(Node* node, int val) {
        if (!node) return nullptr;
        if (val < node->value) node->left = remove(node->left, val);
        else if (val > node->value) node->right = remove(node->right, val);
        else {
            if (!node->left) { Node* temp = node->right; delete node; return temp; }
            if (!node->right) { Node* temp = node->left; delete node; return temp; }
            Node* minNode = node->right;
            while (minNode->left) minNode = minNode->left;
            node->value = minNode->value;
            node->right = remove(node->right, minNode->value);
        }
        return node;
    }

    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}
    ~BST() { clear(root); }
    void add(int val) { root = insert(root, val); }
    void del(int val) { root = remove(root, val); }
    void reset() { clear(root); root = nullptr; }
    Node* getRoot() { return root; }
};

// класс отрисовка
class Drawer {
private:
    sf::Font& font;
    bool isFontLoaded;
    const float RADIUS = 25.0f;

    void drawNode(sf::RenderWindow& win, Node* node, float x, float y, float x_offset) {
        if (!node) return;

        if (node->left) {
            sf::Vertex line[] = { sf::Vertex(sf::Vector2f(x, y)), sf::Vertex(sf::Vector2f(x - x_offset, y + 60)) };
            win.draw(line, 2, sf::Lines);
            drawNode(win, node->left, x - x_offset, y + 60, x_offset / 1.5f);
        }
        if (node->right) {
            sf::Vertex line[] = { sf::Vertex(sf::Vector2f(x, y)), sf::Vertex(sf::Vector2f(x + x_offset, y + 60)) };
            win.draw(line, 2, sf::Lines);
            drawNode(win, node->right, x + x_offset, y + 60, x_offset / 1.5f);
        }

        sf::CircleShape circle(RADIUS);
        circle.setOrigin(RADIUS, RADIUS);
        circle.setPosition(x, y);
        circle.setFillColor(sf::Color::White);
        circle.setOutlineColor(sf::Color::Red);
        circle.setOutlineThickness(2);
        win.draw(circle);

        if (isFontLoaded) {
            sf::Text text;
            text.setFont(font);
            text.setString(std::to_string(node->value));
            text.setCharacterSize(16);
            text.setFillColor(sf::Color::Black);
            sf::FloatRect bounds = text.getLocalBounds();
            text.setOrigin(bounds.left + bounds.width/2, bounds.top + bounds.height/2);
            text.setPosition(x, y);
            win.draw(text);
        }
    }

public:
    Drawer(sf::Font& f, bool loaded) : font(f), isFontLoaded(loaded) {}
    void draw(sf::RenderWindow& win, Node* root) {
        if (root) drawNode(win, root, 600, 80, 200);
    }
};

//класс интерфейс
class AppUI {
public:
    sf::Text title, status;
    std::string input;
    bool isFontLoaded;
    
    AppUI(sf::Font& f, bool loaded) : isFontLoaded(loaded) {
        if (isFontLoaded) {
            title.setFont(f); title.setString("Дерево поиска"); title.setCharacterSize(30); title.setPosition(50, 20); title.setFillColor(sf::Color::Blue);
            status.setFont(f); status.setString("Готово"); status.setCharacterSize(18); status.setPosition(50, 650); status.setFillColor(sf::Color::Black);
        }
    }

    void draw(sf::RenderWindow& win) {
        if (isFontLoaded) {
            win.draw(title);
            win.draw(status);
        }
    }
};

// Главный цикл
int main() {
    sf::RenderWindow window(sf::VideoMode(1200, 700), "Дерево поиска");
    window.setFramerateLimit(60);

    sf::Font font;
    bool fontLoaded = false;
    // Обновленные пути
    std::vector<std::string> paths = {
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
        "C:/Windows/Fonts/arial.ttf"
    };

    for (const auto& path : paths) {
        if (font.loadFromFile(path)) { fontLoaded = true; break; }
    }

    BST tree;
    Drawer drawer(font, fontLoaded);
    AppUI ui(font, fontLoaded);

    sf::Text inputText;
    if (fontLoaded) {
        inputText.setFont(font);
        inputText.setCharacterSize(20);
        inputText.setFillColor(sf::Color::Blue);
        inputText.setPosition(50, 600);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode >= '0' && event.text.unicode <= '9') {
                    ui.input += static_cast<char>(event.text.unicode);
                } else if (event.text.unicode == 8 && !ui.input.empty()) {
                    ui.input.pop_back();
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter && !ui.input.empty()) {
                    tree.add(std::stoi(ui.input));
                    ui.status.setString("Добавлено: " + ui.input);
                    ui.input = "";
                }
                if (event.key.code == sf::Keyboard::D && !ui.input.empty()) {
                    tree.del(std::stoi(ui.input));
                    ui.status.setString("Удалено: " + ui.input);
                    ui.input = "";
                }
                if (event.key.code == sf::Keyboard::C) {
                    tree.reset();
                    ui.status.setString("Дерево очищено");
                }
            }
        }

        window.clear(sf::Color(240, 240, 240));
        
        drawer.draw(window, tree.getRoot());
        ui.draw(window);
        
        if (fontLoaded) {
            inputText.setString("Ввод: " + ui.input);
            window.draw(inputText);
        }
        
        window.display();
    }
    return 0;
}