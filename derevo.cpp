#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib> 
using namespace std;
using namespace sf;

struct Node {
    int value;
    Node* left;
    Node* right;
};


Node* root = nullptr;


Node* insert(Node* node, int val) {
    if (node == nullptr) {
        Node* newNode = new Node;
        newNode->value = val;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }

    if (val < node->value) {
        node->left = insert(node->left, val);
    }
    else if (val > node->value) {
        node->right = insert(node->right, val);
    }
    return node;
}


void drawTree(RenderWindow& window, Node* node, float x, float y, float offset, Font& font) {
    if (node == nullptr) return;


    if (node->left != nullptr) {
        Vertex line[] = {
            Vertex(Vector2f(x, y)),
            Vertex(Vector2f(x - offset, y + 80))
        };
        window.draw(line, 2, Lines);
    }
    if (node->right != nullptr) {
        Vertex line[] = {
            Vertex(Vector2f(x, y)),
            Vertex(Vector2f(x + offset, y + 80))
        };
        window.draw(line, 2, Lines);
    }


    CircleShape circle(25);
    circle.setFillColor(Color::Green);
    circle.setOutlineThickness(2);
    circle.setOutlineColor(Color::Black);
    circle.setPosition(x - 25, y - 25);
    window.draw(circle);


    Text text;
    text.setFont(font);
    text.setString(to_string(node->value));
    text.setCharacterSize(20);
    text.setFillColor(Color::White);

    FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
    text.setPosition(x, y);
    window.draw(text);


    drawTree(window, node->left, x - offset, y + 80, offset * 0.7f, font);
    drawTree(window, node->right, x + offset, y + 80, offset * 0.7f, font);
}

int main() {
    RenderWindow window(VideoMode(800, 600), "Дерево поиска");

    Font font;
    if (!font.loadFromFile("arial.ttf")) {
        if (!font.loadFromFile("C:/Windows/Fonts/Arial.ttf")) {
        }
    }

    string inputString = "";
    Text inputDisplay("", font, 20);
    inputDisplay.setFillColor(Color::White);
    inputDisplay.setPosition(10, 550);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();


            if (event.type == Event::TextEntered) {
                if (event.text.unicode == 8) {
                    if (inputString.length() > 0)
                        inputString.pop_back();
                }
                else if (event.text.unicode == 13) { 
                    if (inputString.length() > 0) {
                        int number = atoi(inputString.c_str());
                        root = insert(root, number);
                        inputString = "";
                    }
                }
                else if (event.text.unicode >= 48 && event.text.unicode <= 57) {
                    inputString += static_cast<char>(event.text.unicode);
                }
                else if (event.text.unicode == '-') {
                    if (inputString.empty())
                        inputString += '-';
                }
            }
        }

        window.clear(Color(100,100,100));

        if (root != nullptr) {
            drawTree(window, root, 400, 50, 200, font);
        }


        inputDisplay.setString("Узлы древа: " + inputString);
        window.draw(inputDisplay);

        window.display();
    }



    return 0;
}
