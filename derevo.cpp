#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

using namespace std;

// узел
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// само дерево
class BST {
public:
    Node* root = nullptr;

    Node* insert(Node* node, int value) {
        if (!node) return new Node(value);

        if (value < node->data)
            node->left = insert(node->left, value);
        else if (value > node->data)
            node->right = insert(node->right, value);

        return node;
    }

    Node* findMin(Node* node) {
        while (node && node->left)
            node = node->left;
        return node;
    }

    Node* remove(Node* node, int value) {
        if (!node) return nullptr;

        if (value < node->data)
            node->left = remove(node->left, value);
        else if (value > node->data)
            node->right = remove(node->right, value);
        else {
            // 0 или 1 ребенок
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // 2 ребенка
            Node* temp = findMin(node->right);
            node->data = temp->data;
            node->right = remove(node->right, temp->data);
        }

        return node;
    }
};


void drawTree(sf::RenderWindow& window, Node* node, float x, float y, float offset, sf::Font& font) {
    if (!node) return;

    // линии (ЧЕРНЫЕ!)
    if (node->left) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x, y), sf::Color::Black),
            sf::Vertex(sf::Vector2f(x - offset, y + 80), sf::Color::Black)
        };
        window.draw(line, 2, sf::Lines);
        drawTree(window, node->left, x - offset, y + 80, offset / 1.5, font);
    }

    if (node->right) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x, y), sf::Color::Black),
            sf::Vertex(sf::Vector2f(x + offset, y + 80), sf::Color::Black)
        };
        window.draw(line, 2, sf::Lines);
        drawTree(window, node->right, x + offset, y + 80, offset / 1.5, font);
    }

    // круг
    sf::CircleShape circle(20);
    circle.setFillColor(sf::Color(100, 150, 250));
    circle.setPosition(x - 20, y - 20);
    window.draw(circle);

    // текст
    sf::Text text;
    text.setFont(font);
    text.setString(to_string(node->data));
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::White);
    text.setPosition(x - 10, y - 15);
    window.draw(text);
}


int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 700), "BST Visual");

    sf::Font font;
    font.loadFromFile("arial.ttf"); 

    BST tree;
    string input = "";

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Ввод текста
            if (event.type == sf::Event::TextEntered) {
                if (isdigit(event.text.unicode)) {
                    input += static_cast<char>(event.text.unicode);
                }
                else if (event.text.unicode == 8 && !input.empty()) { // backspace
                    input.pop_back();
                }
            }

            // Кнопки
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter && !input.empty()) {
                    int value = stoi(input);
                    tree.root = tree.insert(tree.root, value);
                    input = "";
                }

                if (event.key.code == sf::Keyboard::Delete && !input.empty()) {
                    int value = stoi(input);
                    tree.root = tree.remove(tree.root, value);
                    input = "";
                }
            }
        }

        window.clear(sf::Color::White);

        // рисуем дерево
        drawTree(window, tree.root, 500, 80, 200, font);

        // поле ввода
        sf::Text inputText;
        inputText.setFont(font);
        inputText.setString("Input: " + input + " (Enter=add, Delete=remove)");
        inputText.setCharacterSize(20);
        inputText.setFillColor(sf::Color::Black);
        inputText.setPosition(20, 20);
        window.draw(inputText);

        window.display();
    }

    return 0;
}
