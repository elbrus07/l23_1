#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace std;

// все переменные
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float NODE_RADIUS = 30.f;
const float START_X = 400.f;
const float START_Y = 50.f;
const float START_OFFSET = 200.f;
const float LEVEL_HEIGHT = 80.f;
const string FONT_FILE = "arial.ttf";
struct TreeNode
{
    int value;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int val)
    {
        value = val;
        left = nullptr;
        right = nullptr;
    }
};
class BinarySearchTree
{
private:
    TreeNode *root;
    int highlightedValue;
    bool isHighlighted;
    TreeNode *insertNode(TreeNode *node, int value)
    {
        if (!node)
            return new TreeNode(value);
        if (value < node->value)
            node->left = insertNode(node->left, value);
        else
            node->right = insertNode(node->right, value);
        return node;
    }
    bool searchNode(TreeNode *node, int value)
    {
        if (!node)
            return false;
        if (node->value == value)
            return true;
        if (value < node->value)
            return searchNode(node->left, value);
        else
            return searchNode(node->right, value);
    }
    TreeNode *findMinNode(TreeNode *node)
    {
        while (node->left)
            node = node->left;
        return node;
    }
    TreeNode *deleteNode(TreeNode *node, int value)
    {
        if (!node)
            return nullptr;
        if (value < node->value)
            node->left = deleteNode(node->left, value);
        else if (value > node->value)
            node->right = deleteNode(node->right, value);
        else
        {
            if (!node->left && !node->right)
            {
                delete node;
                return nullptr;
            }
            else if (!node->left)
            {
                TreeNode *temp = node->right;
                delete node;
                return temp;
            }
            else if (!node->right)
            {
                TreeNode *temp = node->left;
                delete node;
                return temp;
            }
            else
            {
                TreeNode *temp = findMinNode(node->right);
                node->value = temp->value;
                node->right = deleteNode(node->right, temp->value);
            }
        }
        return node;
    }
    void drawTree(sf::RenderWindow &window, TreeNode *node,
                  float x, float y, float offset, sf::Font &font)
    {
        if (!node)
            return;
        sf::CircleShape circle(NODE_RADIUS);
        if (isHighlighted && node->value == highlightedValue)
            circle.setFillColor(sf::Color::Red);
        else
            circle.setFillColor(sf::Color::White);
        circle.setOutlineColor(sf::Color::Black);
        circle.setOutlineThickness(2);
        circle.setPosition(x, y);
        window.draw(circle);
        sf::Text text;
        text.setFont(font);
        text.setString(to_string(node->value));
        text.setCharacterSize(16);
        text.setFillColor(sf::Color::Black);
        text.setPosition(x + 8, y + 5);
        window.draw(text);
        if (node->left)
        {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x + NODE_RADIUS, y + NODE_RADIUS), sf::Color::Black),
                sf::Vertex(sf::Vector2f(x - offset + NODE_RADIUS, y + LEVEL_HEIGHT), sf::Color::Black)};
            window.draw(line, 2, sf::Lines);
            drawTree(window, node->left, x - offset, y + LEVEL_HEIGHT, offset / 2, font);
        }
        if (node->right)
        {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x + NODE_RADIUS, y + NODE_RADIUS), sf::Color::Black),
                sf::Vertex(sf::Vector2f(x + offset + NODE_RADIUS, y + LEVEL_HEIGHT), sf::Color::Black)};
            window.draw(line, 2, sf::Lines);
            drawTree(window, node->right, x + offset, y + LEVEL_HEIGHT, offset / 2, font);
        }
    }

public:
    BinarySearchTree()
    {
        root = nullptr;
        isHighlighted = false;
    }
    void insert(int value)
    {
        root = insertNode(root, value);
        isHighlighted = false;
    }
    void remove(int value)
    {
        root = deleteNode(root, value);
        isHighlighted = false;
    }
    bool search(int value)
    {
        bool found = searchNode(root, value);

        if (found)
        {
            highlightedValue = value;
            isHighlighted = true;
        }
        else
        {
            isHighlighted = false;
        }
        return found;
    }
    void draw(sf::RenderWindow &window, sf::Font &font)
    {
        drawTree(window, root, START_X, START_Y, START_OFFSET, font);
    }
};
int main()
{
    BinarySearchTree tree;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "BST");
    sf::Font font;
    font.loadFromFile(FONT_FILE);
    string inputText = "";
    string mode = "";
    sf::Text uiText;
    uiText.setFont(font);
    uiText.setCharacterSize(20);
    uiText.setFillColor(sf::Color::Black);
    uiText.setPosition(10, 550);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode >= '0' && event.text.unicode <= '9')
                    inputText += static_cast<char>(event.text.unicode);

                if (event.text.unicode == 8 && !inputText.empty())
                    inputText.pop_back();
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::A)
                {
                    mode = "add";
                    inputText = "";
                }
                if (event.key.code == sf::Keyboard::R)
                {
                    mode = "remove";
                    inputText = "";
                }
                if (event.key.code == sf::Keyboard::F)
                {
                    mode = "find";
                    inputText = "";
                }
                if (event.key.code == sf::Keyboard::Enter && !inputText.empty())
                {
                    int value = stoi(inputText);
                    if (mode == "add")
                        tree.insert(value);
                    if (mode == "remove")
                        tree.remove(value);
                    if (mode == "find")
                        cout << "Find " << value << ": " << tree.search(value) << endl;
                    inputText = "";
                }
            }
        }
        window.clear(sf::Color::White);
        tree.draw(window, font);
        uiText.setString("mode: " + mode + " | input : " + inputText +
                         " | A-add R-remove F-find");
        window.draw(uiText);
        window.display();
    }
    return 0;
}