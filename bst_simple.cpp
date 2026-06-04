#include <algorithm>
#include <cmath>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include <SFML/Graphics.hpp>

using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int v) : key(v), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node* root;

    // Рекурсивная вставка: идем влево/вправо, пока не найдем пустое место.
    static Node* insertRec(Node* n, int value) {
        if (n == nullptr) return new Node(value);
        if (value < n->key) n->left = insertRec(n->left, value);
        else if (value > n->key) n->right = insertRec(n->right, value);
        return n;
    }

    // Минимум в поддереве.
    static Node* findMin(Node* n) {
        while (n->left != nullptr) n = n->left;
        return n;
    }

    // Удаление узла со стандартными 3 случаями:
    // 1) лист
    // 2) один потомок
    // 3) два потомка 
    static Node* removeRec(Node* n, int value) {
        if (n == nullptr) return nullptr;

        if (value < n->key) {
            n->left = removeRec(n->left, value);
        } else if (value > n->key) {
            n->right = removeRec(n->right, value);
        } else {
            if (n->left == nullptr && n->right == nullptr) {
                delete n;
                return nullptr;
            }
            if (n->left == nullptr) {
                Node* t = n->right;
                delete n;
                return t;
            }
            if (n->right == nullptr) {
                Node* t = n->left;
                delete n;
                return t;
            }
            Node* m = findMin(n->right);
            n->key = m->key;
            n->right = removeRec(n->right, m->key);
        }
        return n;
    }

    // Три классических обхода дерева.
    static void preorderRec(Node* n, vector<int>& out) {
        if (n == nullptr) return;
        out.push_back(n->key);
        preorderRec(n->left, out);
        preorderRec(n->right, out);
    }

    static void inorderRec(Node* n, vector<int>& out) {
        if (n == nullptr) return;
        inorderRec(n->left, out);
        out.push_back(n->key);
        inorderRec(n->right, out);
    }

    static void postorderRec(Node* n, vector<int>& out) {
        if (n == nullptr) return;
        postorderRec(n->left, out);
        postorderRec(n->right, out);
        out.push_back(n->key);
    }

    static void clearRec(Node* n) {
        if (n == nullptr) return;
        clearRec(n->left);
        clearRec(n->right);
        delete n;
    }

public:
    BST() : root(nullptr) {}

    ~BST() {
        clearRec(root);
    }

    void insert(int value) { root = insertRec(root, value); }
    void remove(int value) { root = removeRec(root, value); }

    void clearTree() {
        clearRec(root);
        root = nullptr;
    }

    void rotateLeftRoot() {
        if (root == nullptr || root->right == nullptr) return;
        Node* newRoot = root->right;
        root->right = newRoot->left;
        newRoot->left = root;
        root = newRoot;
    }

    void rotateRightRoot() {
        if (root == nullptr || root->left == nullptr) return;
        Node* newRoot = root->left;
        root->left = newRoot->right;
        newRoot->right = root;
        root = newRoot;
    }

    Node* getRoot() const { return root; }
    bool empty() const { return root == nullptr; }

    vector<int> prefix() const {
        vector<int> out;
        preorderRec(root, out);
        return out;
    }

    vector<int> infix() const {
        vector<int> out;
        inorderRec(root, out);
        return out;
    }

    vector<int> postfix() const {
        vector<int> out;
        postorderRec(root, out);
        return out;
    }

    vector<int> toInfixList() const { return infix(); }
};

static string join(const vector<int>& v) {
    if (v.empty()) return "(empty)";
    ostringstream o;
    for (size_t i = 0; i < v.size(); ++i) {
        if (i) o << ' ';
        o << v[i];
    }
    return o.str();
}

static bool inRect(float px, float py, float rx, float ry, float rw, float rh) {
    return px >= rx && px <= rx + rw && py >= ry && py <= ry + rh;
}

static bool parseInt(const string& s, int& out) {
    try {
        size_t p = 0;
        long long v = stoll(s, &p);
        if (p != s.size()) return false;
        if (v < INT_MIN || v > INT_MAX) return false;
        out = static_cast<int>(v);
        return true;
    } catch (...) {
        return false;
    }
}

static void collectPositions(Node* n, int depth, int& index,
                             unordered_map<Node*, sf::Vector2f>& pos,
                             float xStep, float yStep, float startY) {
    if (n == nullptr) return;
    collectPositions(n->left, depth + 1, index, pos, xStep, yStep, startY);
    float x = static_cast<float>(index) * xStep;
    float y = startY + static_cast<float>(depth) * yStep;
    pos[n] = {x, y};
    index++;
    collectPositions(n->right, depth + 1, index, pos, xStep, yStep, startY);
}

static void drawTree(Node* n, sf::RenderWindow& window, sf::Font& font,
                     const unordered_map<Node*, sf::Vector2f>& pos) {
    if (n == nullptr) return;

    const float r = 22.f;
    sf::Vector2f p = pos.at(n);

    if (n->left != nullptr) {
        sf::Vector2f lp = pos.at(n->left);
        sf::Vertex line[] = {{p, sf::Color(190, 190, 210)}, {lp, sf::Color(190, 190, 210)}};
        window.draw(line, 2, sf::PrimitiveType::Lines);
        drawTree(n->left, window, font, pos);
    }
    if (n->right != nullptr) {
        sf::Vector2f rp = pos.at(n->right);
        sf::Vertex line[] = {{p, sf::Color(190, 190, 210)}, {rp, sf::Color(190, 190, 210)}};
        window.draw(line, 2, sf::PrimitiveType::Lines);
        drawTree(n->right, window, font, pos);
    }

    float sx = round(p.x);
    float sy = round(p.y);
    sf::CircleShape c(r);
    c.setOrigin({r, r});
    c.setPosition({sx, sy});
    c.setFillColor(sf::Color(70, 130, 180));
    c.setOutlineColor(sf::Color::White);
    c.setOutlineThickness(2.f);
    window.draw(c);

    sf::Text t(font);
    t.setCharacterSize(17);
    t.setFillColor(sf::Color::White);
    t.setString(to_string(n->key));
    sf::FloatRect b = t.getLocalBounds();
    t.setOrigin({b.position.x + b.size.x / 2.f, b.position.y + b.size.y / 2.f});
    t.setPosition({sx, sy - 1.f});
    window.draw(t);
}

static void runWindow(BST& tree, sf::Font& font) {
    const unsigned W = 1100;
    const unsigned H = 860;
    const float panelH = 250.f;
    const float treeBottom = static_cast<float>(H) - panelH;

    sf::RenderWindow window(sf::VideoMode({W, H}), "BST Simple");
    window.setFramerateLimit(60);

    sf::View treeView(sf::FloatRect({0.f, 0.f}, {static_cast<float>(W), treeBottom}));
    treeView.setCenter({static_cast<float>(W) / 2.f, treeBottom / 2.f});
    treeView.setViewport(sf::FloatRect({0.f, 0.f}, {1.f, treeBottom / static_cast<float>(H)}));

    // Перетаскивание камеры через ПКМ
    bool dragging = false;
    sf::Vector2i lastMouse(0, 0);
    string input;
    string status = "Use buttons. Enter = Insert.";

    auto drawText = [&](float x, float y, const string& s, unsigned sz, const sf::Color& col) {
        sf::Text t(font);
        t.setCharacterSize(sz);
        t.setFillColor(col);
        t.setString(s);
        t.setPosition({x, y});
        window.draw(t);
    };

    auto drawBtn = [&](float x, float y, float bw, float bh, const string& label, bool hover) {
        sf::RectangleShape bg({bw, bh});
        bg.setPosition({x, y});
        bg.setFillColor(hover ? sf::Color(90, 90, 115) : sf::Color(55, 55, 75));
        bg.setOutlineColor(sf::Color(130, 130, 160));
        bg.setOutlineThickness(1.f);
        window.draw(bg);

        sf::Text t(font);
        t.setCharacterSize(16);
        t.setFillColor(sf::Color::White);
        t.setString(label);
        sf::FloatRect b = t.getLocalBounds();
        t.setOrigin({b.position.x + b.size.x / 2.f, b.position.y + b.size.y / 2.f});
        t.setPosition({round(x + bw / 2.f), round(y + bh / 2.f)});
        window.draw(t);
    };

    while (window.isOpen()) {
        const sf::Vector2i mouse = sf::Mouse::getPosition(window);

        while (const optional<sf::Event> ev = window.pollEvent()) {
            if (ev->is<sf::Event::Closed>()) window.close();

            if (const auto* key = ev->getIf<sf::Event::KeyPressed>()) {
                if (key->code == sf::Keyboard::Key::Escape) window.close();
                if (key->code == sf::Keyboard::Key::Backspace && !input.empty()) input.pop_back();
                if (key->code == sf::Keyboard::Key::Enter) {
                    int v = 0;
                    if (!parseInt(input, v)) status = "Invalid input.";
                    else {
                        tree.insert(v);
                        status = "Inserted: " + input;
                        input.clear();
                    }
                }
            }

            if (const auto* mm = ev->getIf<sf::Event::MouseMoved>()) {
                if (dragging) {
                    sf::Vector2i cur(mm->position.x, mm->position.y);
                    sf::Vector2f a = window.mapPixelToCoords(lastMouse, treeView);
                    sf::Vector2f b = window.mapPixelToCoords(cur, treeView);
                    treeView.move(a - b);
                    lastMouse = cur;
                }
            }

            if (const auto* mb = ev->getIf<sf::Event::MouseButtonPressed>()) {
                if (mb->button == sf::Mouse::Button::Right && mb->position.y < static_cast<int>(treeBottom)) {
                    dragging = true;
                    lastMouse = mb->position;
                }

                // Кнопки внизу окна: вставка/удаление/повороты/очистка.
                if (mb->button == sf::Mouse::Button::Left) {
                    float mx = static_cast<float>(mb->position.x);
                    float my = static_cast<float>(mb->position.y);
                    float rowY = treeBottom + 106.f;
                    float bw = 118.f, bh = 36.f, gap = 8.f, x0 = 12.f;
                    auto bx = [&](int i) { return x0 + static_cast<float>(i) * (bw + gap); };

                    if (inRect(mx, my, bx(0), rowY, bw, bh)) {
                        int v = 0;
                        if (!parseInt(input, v)) status = "Enter number for insert.";
                        else {
                            tree.insert(v);
                            status = "Inserted: " + input;
                            input.clear();
                        }
                    } else if (inRect(mx, my, bx(1), rowY, bw, bh)) {
                        int v = 0;
                        if (!parseInt(input, v)) status = "Enter number for delete.";
                        else {
                            tree.remove(v);
                            status = "Deleted (if existed): " + input;
                            input.clear();
                        }
                    } else if (inRect(mx, my, bx(2), rowY, bw, bh)) {
                        tree.rotateLeftRoot();
                        status = "Left rotation at root.";
                    } else if (inRect(mx, my, bx(3), rowY, bw, bh)) {
                        tree.rotateRightRoot();
                        status = "Right rotation at root.";
                    } else if (inRect(mx, my, bx(4), rowY, bw, bh)) {
                        input.clear();
                        status = "Input cleared.";
                    } else if (inRect(mx, my, bx(5), rowY, bw, bh)) {
                        tree.clearTree();
                        status = "Tree cleared.";
                    }
                }
            }

            if (const auto* mr = ev->getIf<sf::Event::MouseButtonReleased>()) {
                if (mr->button == sf::Mouse::Button::Right) dragging = false;
            }

            if (const auto* te = ev->getIf<sf::Event::TextEntered>()) {
                char32_t u = te->unicode;
                if (u == 8 || u == 127) continue;
                if (u == U'-' && input.empty()) {
                    input.push_back('-');
                    continue;
                }
                if (u >= U'0' && u <= U'9' && input.size() < 12) input.push_back(static_cast<char>(u));
            }
        }

        window.clear(sf::Color(28, 28, 36));

        if (!tree.empty()) {
            unordered_map<Node*, sf::Vector2f> pos;
            int index = 0;
            collectPositions(tree.getRoot(), 0, index, pos, 84.f, 86.f, 40.f);
            window.setView(treeView);
            drawTree(tree.getRoot(), window, font, pos);
        }

        window.setView(window.getDefaultView());
        sf::RectangleShape panel({static_cast<float>(W), panelH});
        panel.setPosition({0.f, treeBottom});
        panel.setFillColor(sf::Color(22, 22, 30));
        panel.setOutlineColor(sf::Color(50, 50, 65));
        panel.setOutlineThickness(1.f);
        window.draw(panel);

        drawText(12.f, treeBottom + 8.f, status, 14, sf::Color(220, 220, 230));
        drawText(12.f, treeBottom + 34.f, "Value: " + (input.empty() ? string("_") : input), 16, sf::Color::White);
        drawText(12.f, treeBottom + 62.f, "Enter=Insert", 14, sf::Color(200, 200, 215));
        drawText(12.f, treeBottom + 86.f, "Camera: Right click", 14, sf::Color(200, 200, 215));

        float rowY = treeBottom + 106.f;
        float bw = 118.f, bh = 36.f, gap = 8.f, x0 = 12.f;
        float bx = x0;
        float mx = static_cast<float>(mouse.x);
        float my = static_cast<float>(mouse.y);
        auto btn = [&](const string& title) {
            bool hover = inRect(mx, my, bx, rowY, bw, bh);
            drawBtn(bx, rowY, bw, bh, title, hover);
            bx += bw + gap;
        };
        btn("Insert");
        btn("Delete");
        btn("Rotate <<");
        btn("Rotate >>");
        btn("Clear Input");
        btn("Clear Tree");

        window.display();
    }
}

int main() {
    BST tree;

    sf::Font font;
    bool ok = false;
    for (const char* path : {
             "/System/Library/Fonts/Supplemental/Arial.ttf",
             "/System/Library/Fonts/Supplemental/Arial Unicode.ttf",
             "/System/Library/Fonts/Supplemental/DejaVuSans.ttf",
             "/Library/Fonts/Arial.ttf",
             "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
             "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
         }) {
        if (font.openFromFile(path)) {
            ok = true;
            break;
        }
    }
    if (!ok) {
        cout << "Font not found.\n";
        return 1;
    }
    font.setSmooth(false);

    // Консольные команды для управления деревом 
    cout << "Commands:\n";
    cout << "  add N [M ...]   - add one or many values\n";
    cout << "  del N [M ...]   - delete one or many values\n";
    cout << "  clear           - clear whole tree\n";
    cout << "  prefix          - print prefix traversal\n";
    cout << "  infix           - print infix traversal\n";
    cout << "  postfix         - print postfix traversal\n";
    cout << "  list            - print infix list\n";
    cout << "  show            - open SFML window\n";
    cout << "  quit            - exit\n\n";

    while (true) {
        cout << "cmd> ";
        string cmd;
        if (!getline(cin, cmd)) break;

        if (cmd.rfind("add ", 0) == 0) {
            istringstream iss(cmd.substr(4));
            int v = 0;
            bool any = false;
            while (iss >> v) {
                tree.insert(v);
                any = true;
            }
            cout << (any ? "Added.\n" : "Usage: add N [M ...]\n");
        } else if (cmd.rfind("del ", 0) == 0) {
            istringstream iss(cmd.substr(4));
            int v = 0;
            bool any = false;
            while (iss >> v) {
                tree.remove(v);
                any = true;
            }
            cout << (any ? "Deleted (if existed).\n" : "Usage: del N [M ...]\n");
        } else if (cmd == "clear") {
            tree.clearTree();
            cout << "Tree cleared.\n";
        } else if (cmd == "prefix") {
            cout << join(tree.prefix()) << "\n";
        } else if (cmd == "infix") {
            cout << join(tree.infix()) << "\n";
        } else if (cmd == "postfix") {
            cout << join(tree.postfix()) << "\n";
        } else if (cmd == "list") {
            cout << join(tree.toInfixList()) << "\n";
        } else if (cmd == "show") {
            runWindow(tree, font);
        } else if (cmd == "quit" || cmd == "exit") {
            break;
        } else if (cmd.empty()) {
            continue;
        } else {
            cout << "Unknown command. Use: add/del/clear/prefix/infix/postfix/list/show/quit\n";
        }
    }

    return 0;
}
