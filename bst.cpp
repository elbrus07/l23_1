#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};



class BinaryTree {

public:
    BinaryTree() {
        root = nullptr;
    }

    ~BinaryTree() {
        clear(root);
    }

    void insert(int value) {
        /*Функция вставки значения в дерево(вспомогательная)*/
        root = insertNode(root, value);
    }

    bool search(int value) {
        /*Функция поиска значений в дереве(вспомогательная)*/
        return searchNode(root, value);
    }

    void remove(int value) {
        /*Функция удаления значения из дерева(вспомогательная)*/
        root = deleteNode(root, value);
    }

    /*Обходы*/

    vector<int> getPreOrder() {
        /*Прямой обход (root, left, right)(пользовательская)*/
        vector<int> result;
        preOrder(root, result);
        return result;
    }

    vector<int> getInOrder() {
        /*Симметричный обход (left, root, right)(пользовательская)*/
        vector<int> result;
        inOrder(root, result);
        return result;
    }

    vector<int> getPostOrder() {
        /*Обратный обход (left, right, root)(пользовательская)*/
        vector<int> result;
        postOrder(root, result);
        return result;
    }

    bool isEmpty() {
        /*Функци проверки дерева на пустоту*/
        return root == nullptr;
    }

    Node* getRoot() { return root; }

private:
    Node* root;

    Node* insertNode(Node* node, int value) {
        /*функция для рекурсивной вставки значения в дерево*/
        if (node == nullptr) {
            return new Node(value);
        }

        if (value < node->data) {
            node->left = insertNode(node->left, value);
        }
        else if (value > node->data) {
            node->right = insertNode(node->right, value);
        }

        return node;
    }

    bool searchNode(Node* node, int value) {
        /*функция для рекурсивного поиска значения в дереве*/
        if (node == nullptr) return false;

        if (node->data == value) return true;

        if (value < node->data) {
            return searchNode(node->left, value);
        }
        else {
            return searchNode(node->right, value);
        }
    }

    Node* findMin(Node* node) {
        /*Функция для нахождения миниума в поддереве*/
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Node* deleteNode(Node* node, int value) {
        /*Функция для рекурсивного удаления узла*/
        if (node == nullptr) return nullptr;

        if (value < node->data) {
            node->left = deleteNode(node->left, value);
        }
        else if (value > node->data) {
            node->right = deleteNode(node->right, value);
        }
        else {
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }

            else if (node->left/*Указатель на левого ребенка*/ == nullptr) {
                Node* child = node->right;
                delete node;
                return child;
            }
            else if (node->right == nullptr) {
                Node* child = node->left;
                delete node;
                return child;
            }
            else {
                Node* minNode = findMin(node->right);
                node->data = minNode->data;
                node->right = deleteNode(node->right, minNode->data);
            }
        }
        return node;
    }

    /*обходы*/

    void preOrder(Node* node, vector<int>& result) {
        /*Прямой обход (root, left, right)(основная)*/
        if (node == nullptr) return;
        result.push_back(node->data);
        preOrder(node->left, result);
        preOrder(node->right, result);
    }

    void inOrder(Node* node, vector<int>& result) {
        /*Симметричный обход (left, root, right)(основная)*/
        if (node == nullptr) return;
        inOrder(node->left, result);
        result.push_back(node->data);
        inOrder(node->right, result);
    }

    void postOrder(Node* node, vector<int>& result) {
        /*Обратный обход (left, right, root)(основная)*/
        if (node == nullptr) return;
        postOrder(node->left, result);
        postOrder(node->right, result);
        result.push_back(node->data);
    }

    // Очистка дерева
    void clear(Node* node) {
        /*Удаление всего дерева*/
        if (node == nullptr) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }
};

class TreeDrawer {
    /*класс для рисования BST*/
public:
    TreeDrawer() {
        string path = "C:/Users/1/source/repos/sfml2/x64/Debug/arial.ttf";
        if (!font.loadFromFile(path)) {
            cout << "Шрифт не загружен" << endl;
        }
        else {
            cout << "Шрифт загружен" << endl;
        }
    }

    void run(BinaryTree& tree) {
        RenderWindow window(VideoMode(800, 600), "Binary Tree");

        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed)
                    window.close();
            }

            window.clear(Color(0, 0, 0));

            if (!tree.isEmpty()) {
                drawNode(window, tree.getRoot(), 400, 50, 200);
            }

            window.display();
        }
    }
private:
    Font font;

    void drawNode(RenderWindow& window, Node* node, float x, float y, float dest_x) {
        /*Функция для отрисовки дерева*/
        if (node == nullptr) return;
        if (node->left) {
            Vertex line[] = {
                Vertex(Vector2f(x, y), Color(100,100,100)),
                Vertex(Vector2f(x - dest_x, y + 70), Color(100,100,100))
            };
            window.draw(line, 2, Lines);
            drawNode(window, node->left, x - dest_x, y + 70, dest_x / 2);
        }

        if (node->right) {
            Vertex line[] = {
                Vertex(Vector2f(x, y), Color(100,100,100)),
                Vertex(Vector2f(x + dest_x, y + 70), Color(100,100,100))
            };
            window.draw(line, 2, Lines);
            drawNode(window, node->right, x + dest_x, y + 70, dest_x / 2);
        }

        CircleShape circle(25);
        circle.setPosition(x - 25, y - 25);
        circle.setFillColor(Color(100, 100, 100));
        circle.setOutlineThickness(2);
        window.draw(circle);

        Text text;
        text.setFont(font);
        text.setString(to_string(node->data));
        text.setCharacterSize(18);
        FloatRect bounds = text.getLocalBounds();
        text.setPosition(x - bounds.width / 2, y - bounds.height / 2 - 2);
        window.draw(text);
    }

};

int main() {
    BinaryTree tree;

    tree.insert(50);
    tree.insert(30);
    tree.insert(65);
    tree.insert(20);
    tree.insert(21);
    tree.insert(17);
    tree.insert(71);
    tree.insert(80);
    cout << "\nSearch 50: " << (tree.search(50)) << endl;
    cout << "Search 100: " << (tree.search(100)) << endl;

    cout << "\nDelete 30" << endl;
    tree.remove(30);

    vector<int> PreOrder = tree.getPreOrder();
    for (int i = 0; i < PreOrder.size(); i++) {
        cout << PreOrder[i] << " ";
    }

    cout << endl;

    vector<int> InOrder = tree.getInOrder();
    for (int i = 0; i < InOrder.size(); i++) {
        cout << InOrder[i] << " ";
    }

    cout << endl;

    vector<int> PostOrder = tree.getPostOrder();
    for (int i = 0; i < PostOrder.size(); i++) {
        cout << PostOrder[i] << " ";
    }

    cout << endl;

    TreeDrawer visualizer;
    visualizer.run(tree);

    return 0;
}