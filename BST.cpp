#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <string>
#include <vector>
#include <sstream>

class Node
{
public:
    int value;
    Node* left;
    Node* right;

    explicit Node(int value)
        : value(value), left(nullptr), right(nullptr)
    {
    }
};

class BinarySearchTree
{
private:
    Node* root;

    Node* insert(Node* node, int value)
    {
        if (!node)
            return new Node(value);

        if (value < node->value)
            node->left = insert(node->left, value);
        else if (value > node->value)
            node->right = insert(node->right, value);

        return node;
    }

    Node* findMin(Node* node)
    {
        while (node && node->left)
            node = node->left;

        return node;
    }

    Node* remove(Node* node, int value)
    {
        if (!node)
            return nullptr;

        if (value < node->value)
            node->left = remove(node->left, value);
        else if (value > node->value)
            node->right = remove(node->right, value);
        else
        {
            if (!node->left)
            {
                Node* temp = node->right;
                delete node;
                return temp;
            }

            if (!node->right)
            {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = findMin(node->right);
            node->value = temp->value;
            node->right = remove(node->right, temp->value);
        }

        return node;
    }

    void destroy(Node* node)
    {
        if (!node)
            return;

        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    void inorder(Node* node, std::vector<int>& result)
    {
        if (!node)
            return;

        inorder(node->left, result);
        result.push_back(node->value);
        inorder(node->right, result);
    }

    void preorder(Node* node, std::vector<int>& result)
    {
        if (!node)
            return;

        result.push_back(node->value);
        preorder(node->left, result);
        preorder(node->right, result);
    }

    void postorder(Node* node, std::vector<int>& result)
    {
        if (!node)
            return;

        postorder(node->left, result);
        postorder(node->right, result);
        result.push_back(node->value);
    }

public:
    BinarySearchTree()
        : root(nullptr)
    {
    }

    ~BinarySearchTree()
    {
        destroy(root);
    }

    void insert(int value)
    {
        root = insert(root, value);
    }

    void remove(int value)
    {
        root = remove(root, value);
    }

    Node* getRoot() const
    {
        return root;
    }

    std::vector<int> inorder()
    {
        std::vector<int> result;
        inorder(root, result);
        return result;
    }

    std::vector<int> preorder()
    {
        std::vector<int> result;
        preorder(root, result);
        return result;
    }

    std::vector<int> postorder()
    {
        std::vector<int> result;
        postorder(root, result);
        return result;
    }
};

class InputBox
{
private:
    std::string text;

public:
    void addCharacter(char c)
    {
        if ((c >= '0' && c <= '9') || (c == '-' && text.empty()))
            text += c;
    }

    void eraseLast()
    {
        if (!text.empty())
            text.pop_back();
    }

    bool empty() const
    {
        return text.empty() || text == "-";
    }

    int value() const
    {
        return std::stoi(text);
    }

    void clear()
    {
        text.clear();
    }

    const std::string& getText() const
    {
        return text;
    }
};

enum class TraversalType
{
    InOrder,
    PreOrder,
    PostOrder
};

enum class Mode
{
    Add,
    Delete
};

class TreeRenderer
{
private:
    sf::Font font;

    void drawNode(
        sf::RenderWindow& window,
        Node* node,
        float x,
        float y,
        float offset)
    {
        if (!node)
            return;

        if (node->left)
        {
            float childX = x - offset;
            float childY = y + 90.f;

            sf::Vertex line[] =
            {
                sf::Vertex({x, y}, sf::Color::White),
                sf::Vertex({childX, childY}, sf::Color::White)
            };

            window.draw(line, 2, sf::PrimitiveType::Lines);

            drawNode(
                window,
                node->left,
                childX,
                childY,
                offset * 0.55f
            );
        }

        if (node->right)
        {
            float childX = x + offset;
            float childY = y + 90.f;

            sf::Vertex line[] =
            {
                sf::Vertex({x, y}, sf::Color::White),
                sf::Vertex({childX, childY}, sf::Color::White)
            };

            window.draw(line, 2, sf::PrimitiveType::Lines);

            drawNode(
                window,
                node->right,
                childX,
                childY,
                offset * 0.55f
            );
        }

        sf::CircleShape circle(25.f);
        circle.setOrigin({25.f, 25.f});
        circle.setPosition({x, y});
        circle.setFillColor(sf::Color(50, 120, 255));
        circle.setOutlineThickness(2.f);
        circle.setOutlineColor(sf::Color::White);

        window.draw(circle);

        sf::Text text(font);
        text.setCharacterSize(18);
        text.setString(std::to_string(node->value));
        text.setFillColor(sf::Color::White);

        auto bounds = text.getLocalBounds();

        text.setPosition({
            x - bounds.size.x / 2.f,
            y - bounds.size.y
        });

        window.draw(text);
    }

public:
    explicit TreeRenderer(const sf::Font& externalFont)
    {
        font = externalFont;
    }

    void draw(sf::RenderWindow& window, Node* root)
    {
        if (!root)
            return;

        drawNode(
            window,
            root,
            window.getSize().x / 2.f,
            120.f,
            220.f
        );
    }
};

class Application
{
private:
    sf::RenderWindow window;
    sf::Font font;

    BinarySearchTree tree;
    InputBox input;
    TreeRenderer* renderer;

    TraversalType traversal;
    Mode mode;

    std::string traversalString()
    {
        std::vector<int> values;

        switch (traversal)
        {
            case TraversalType::InOrder:
                values = tree.inorder();
                break;

            case TraversalType::PreOrder:
                values = tree.preorder();
                break;

            case TraversalType::PostOrder:
                values = tree.postorder();
                break;
        }

        std::stringstream ss;

        for (size_t i = 0; i < values.size(); i++)
        {
            ss << values[i];

            if (i + 1 < values.size())
                ss << ' ';
        }

        return ss.str();
    }

    void processText(uint32_t unicode)
    {
        if (unicode >= 32 && unicode < 127)
            input.addCharacter(static_cast<char>(unicode));
    }

    void executeAction()
    {
        if (input.empty())
            return;

        int value = input.value();

        if (mode == Mode::Add)
            tree.insert(value);
        else
            tree.remove(value);

        input.clear();
    }

    void processEvents()
    {
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (const auto* text = event->getIf<sf::Event::TextEntered>())
                processText(text->unicode);

            if (const auto* key = event->getIf<sf::Event::KeyPressed>())
            {
                switch (key->code)
                {
                    case sf::Keyboard::Key::Enter:
                        executeAction();
                        break;

                    case sf::Keyboard::Key::Backspace:
                        input.eraseLast();
                        break;

                    case sf::Keyboard::Key::A:
                        mode = Mode::Add;
                        break;

                    case sf::Keyboard::Key::D:
                        mode = Mode::Delete;
                        break;

                    case sf::Keyboard::Key::Num1:
                        traversal = TraversalType::InOrder;
                        break;

                    case sf::Keyboard::Key::Num2:
                        traversal = TraversalType::PreOrder;
                        break;

                    case sf::Keyboard::Key::Num3:
                        traversal = TraversalType::PostOrder;
                        break;

                    default:
                        break;
                }
            }
        }
    }

    void drawUI()
    {
        sf::Text title(font);
        title.setCharacterSize(22);

        std::string modeText =
            mode == Mode::Add
            ? "Mode: ADD"
            : "Mode: DELETE";

        title.setString(modeText);
        title.setPosition({20.f, 10.f});

        window.draw(title);

        sf::RectangleShape box({300.f, 40.f});
        box.setPosition({20.f, 45.f});
        box.setFillColor(sf::Color(30, 30, 30));
        box.setOutlineColor(sf::Color::White);
        box.setOutlineThickness(2.f);

        window.draw(box);

        sf::Text inputText(font);
        inputText.setCharacterSize(22);
        inputText.setString(input.getText());
        inputText.setPosition({30.f, 50.f});

        window.draw(inputText);

        sf::Text info(font);
        info.setCharacterSize(18);

        std::string traversalName;

        switch (traversal)
        {
            case TraversalType::InOrder:
                traversalName = "InOrder";
                break;

            case TraversalType::PreOrder:
                traversalName = "PreOrder";
                break;

            case TraversalType::PostOrder:
                traversalName = "PostOrder";
                break;
        }

        info.setString(
            "A - Add | D - Delete | 1 - InOrder | 2 - PreOrder | 3 - PostOrder"
        );

        info.setPosition({350.f, 20.f});

        window.draw(info);

        sf::Text traversalText(font);
        traversalText.setCharacterSize(18);

        traversalText.setString(
            traversalName + ": " + traversalString()
        );

        traversalText.setPosition({
            20.f,
            static_cast<float>(window.getSize().y) - 40.f
        });

        window.draw(traversalText);
    }

    void render()
    {
        window.clear(sf::Color(20, 20, 20));

        renderer->draw(window, tree.getRoot());

        drawUI();

        window.display();
    }

public:
    Application()
        : window(
            sf::VideoMode({1400, 900}),
            "Binary Search Tree"
        ),
          renderer(nullptr),
          traversal(TraversalType::InOrder),
          mode(Mode::Add)
    {
        window.setFramerateLimit(144);

        if (!font.openFromFile("arial.ttf"))
            std::exit(1);

        renderer = new TreeRenderer(font);
    }

    ~Application()
    {
        delete renderer;
    }

    void run()
    {
        while (window.isOpen())
        {
            processEvents();
            render();
        }
    }
};

int main()
{
    Application app;
    app.run();
    return 0;
}