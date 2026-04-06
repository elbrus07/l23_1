#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;


struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BST {
public:
    Node* root;

    BST() : root(nullptr) {}

    Node* insert(Node* node, int val) {
        if (!node) return new Node(val);

        if (val < node->data)
            node->left = insert(node->left, val);
        else if (val > node->data)
            node->right = insert(node->right, val);

        return node;
    }

    void insert(int val) {
        root = insert(root, val);
    }

    bool search(Node* node, int val) {
        if (!node) return false;
        if (node->data == val) return true;

        if (val < node->data)
            return search(node->left, val);
        else
            return search(node->right, val);
    }

    bool search(int val) {
        return search(root, val);
    }

    Node* findMin(Node* node) {
        while (node->left) node = node->left;
        return node;
    }

    Node* remove(Node* node, int val) {
        if (!node) return nullptr;

        if (val < node->data)
            node->left = remove(node->left, val);
        else if (val > node->data)
            node->right = remove(node->right, val);
        else {
            // 1. нет детей
            if (!node->left && !node->right) {
                delete node;
                return nullptr;
            }

            // 2. один ребёнок
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            }

            if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // два ребёнка
            Node* temp = findMin(node->right);
            node->data = temp->data;
            node->right = remove(node->right, temp->data);
        }

        return node;
    }

    void remove(int val) {
        root = remove(root, val);
    }
};


void drawTree(sf::RenderWindow& window, Node* node,
              float x, float y, float offset,
              sf::Font& font) {

    if (!node) return;

    // Линии
    if (node->left) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x, y)),
            sf::Vertex(sf::Vector2f(x - offset, y + 80))
        };
        window.draw(line, 2, sf::Lines);

        drawTree(window, node->left, x - offset, y + 80, offset / 1.5, font);
    }

    if (node->right) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x, y)),
            sf::Vertex(sf::Vector2f(x + offset, y + 80))
        };
        window.draw(line, 2, sf::Lines);

        drawTree(window, node->right, x + offset, y + 80, offset / 1.5, font);
    }

    // Круг
    sf::CircleShape circle(20);
    circle.setFillColor(sf::Color::White);
    circle.setOutlineColor(sf::Color::Black);
    circle.setOutlineThickness(2);
    circle.setPosition(x - 20, y - 20);
    window.draw(circle);

    sf::Text text;
    text.setFont(font);
    text.setString(to_string(node->data));
    text.setCharacterSize(14);
    text.setFillColor(sf::Color::Black);
    text.setPosition(x - 10, y - 12);
    window.draw(text);
}


int main() {
    BST tree;

    int values[] = {8, 3, 10, 1, 6, 14, 4, 7, 13};
    for (int v : values)
        tree.insert(v);

    sf::RenderWindow window(sf::VideoMode(800, 600), "BST Visualization");

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return -1;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window.close();

            // управление 
            if (event.type == sf::Event::KeyPressed) {

                if (event.key.code == sf::Keyboard::A) {
                    int x;
                    cout << "Введите число для добавления: ";
                    cin >> x;
                    tree.insert(x);
                }

                if (event.key.code == sf::Keyboard::D) {
                    int x;
                    cout << "Введите число для удаления: ";
                    cin >> x;
                    tree.remove(x);
                }

                if (event.key.code == sf::Keyboard::S) {
                    int x;
                    cout << "Введите число для поиска: ";
                    cin >> x;
                    cout << (tree.search(x) ? "Найден\n" : "Не найден\n");
                }
            }
        }

        window.clear(sf::Color::White);

        drawTree(window, tree.root, 400, 50, 150, font);

        window.display();
    }

    return 0;
}