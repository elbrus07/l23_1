#include <iostream>
using namespace std;

class BST {
private:
    struct Node {
        int key;
        Node* left;
        Node* right;

        Node(int value) : key(value), left(nullptr), right(nullptr) {}
    };

    Node* root;

    
    Node* insert(Node* node, int key) {
        if (node == nullptr)
            return new Node(key);

        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);

        return node;
    }

    
    Node* search(Node* node, int key) {
        if (node == nullptr || node->key == key)
            return node;

        if (key < node->key)
            return search(node->left, key);

        return search(node->right, key);
    }

   
    Node* findMin(Node* node) {
        while (node && node->left != nullptr)
            node = node->left;
        return node;
    }

    
    Node* remove(Node* node, int key) {
        if (node == nullptr)
            return node;

        if (key < node->key) {
            node->left = remove(node->left, key);
        } else if (key > node->key) {
            node->right = remove(node->right, key);
        } else {
            
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

           
            Node* temp = findMin(node->right);
            node->key = temp->key;
            node->right = remove(node->right, temp->key);
        }
        return node;
    }


    void inorder(Node* node) {
        if (node == nullptr)
            return;

        inorder(node->left);
        cout << node->key << " ";
        inorder(node->right);
    }

public:
    BST() : root(nullptr) {}

    void insert(int key) {
        root = insert(root, key);
    }

    void remove(int key) {
        root = remove(root, key);
    }

    bool search(int key) {
        return search(root, key) != nullptr;
    }

    void traverse() {
        inorder(root);
        cout << endl;
    }
};


int main() {
    BST tree;

    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    cout << "Обход дерева: ";
    tree.traverse();

    cout << "Поиск 40: " << (tree.search(40) ? "Найден" : "Не найден") << endl;

    tree.remove(30);

    cout << "После удаления 30: ";
    tree.traverse();

    return 0;
}