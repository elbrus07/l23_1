#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <string>

using namespace sf;
using namespace std;

sf::String loadFromFile(const string& filename)
{
    ifstream file(filename);

    if (!file.is_open())
        return "";

    stringstream buffer;
    buffer << file.rdbuf();

    string loadedText = buffer.str();

    return sf::String::fromUtf8(
        loadedText.begin(),
        loadedText.end()
    );
}

void saveToFile(const string& filename, const sf::String& text)
{
    ofstream file(filename);

    file << text.toAnsiString();
}

int main()
{
    RenderWindow window(VideoMode(1000, 700), "Mini Notepad");

    //ШРИФТ!!!
    Font font;

    if (!font.loadFromFile("arial.ttf"))
        return -1;

    
    sf::String text;

    Text textDisplay;
    textDisplay.setFont(font);
    textDisplay.setCharacterSize(24);
    textDisplay.setFillColor(Color::Black);
    textDisplay.setPosition(10, 60);

    //панелька
    RectangleShape topBar(Vector2f(1000, 50));
    topBar.setFillColor(Color(220, 220, 220));

    //кнопка сохранения save
    RectangleShape saveButton(Vector2f(120, 35));
    saveButton.setPosition(10, 7);
    saveButton.setFillColor(Color(180, 180, 180));

    Text saveText;
    saveText.setFont(font);
    saveText.setString("Save");
    saveText.setCharacterSize(22);
    saveText.setFillColor(Color::Black);
    saveText.setPosition(40, 10);

    //кнопка open
    RectangleShape openButton(Vector2f(120, 35));
    openButton.setPosition(150, 7);
    openButton.setFillColor(Color(180, 180, 180));

    Text openText;
    openText.setFont(font);
    openText.setString("Open");
    openText.setCharacterSize(22);
    openText.setFillColor(Color::Black);
    openText.setPosition(180, 10);

    //clear кнопка
    RectangleShape clearButton(Vector2f(120, 35));
    clearButton.setPosition(290, 7);
    clearButton.setFillColor(Color(180, 180, 180));

    Text clearText;
    clearText.setFont(font);
    clearText.setString("Clear");
    clearText.setCharacterSize(22);
    clearText.setFillColor(Color::Black);
    clearText.setPosition(320, 10);

    while (window.isOpen())
    {
        Event event;

        while (window.pollEvent(event))
        {
            
            if (event.type == Event::Closed)
                window.close();

            //ввод 
            if (event.type == Event::TextEntered)
            {
                // Backspace
                if (event.text.unicode == 8)
                {
                    if (!text.isEmpty())
                    {
                        text.erase(text.getSize() - 1, 1);
                    }
                }

                // обычные символы
                else if (event.text.unicode >= 32)
                {
                    text += event.text.unicode;
                }
            }

            //горячие клавиши
            if (event.type == Event::KeyPressed)
            {

                // Enter
                if (event.key.code == Keyboard::Enter)
                {
                    text += L'\n';
                }

                // ctrl + S
                if (event.key.control &&
                    event.key.code == Keyboard::S)
                {
                    saveToFile("note.txt", text);
                }

                // ctrl + O
                if (event.key.control &&
                    event.key.code == Keyboard::O)
                {
                    text = loadFromFile("note.txt");
                }
            }

            
            if (event.type == Event::MouseButtonPressed)
            {
                Vector2f mousePos =
                    window.mapPixelToCoords(
                        Mouse::getPosition(window));

                //сохр
                if (saveButton.getGlobalBounds().contains(mousePos))
                {
                    saveToFile("note.txt", text);
                }

                //открвтие
                if (openButton.getGlobalBounds().contains(mousePos))
                {
                    text = loadFromFile("note.txt");
                }

                //очистка
                if (clearButton.getGlobalBounds().contains(mousePos))
                {
                    text.clear();
                }
            }
        }

        
        textDisplay.setString(text);

        //отрисовка всего
        window.clear(Color::White);

        window.draw(topBar);

        window.draw(saveButton);
        window.draw(saveText);

        window.draw(openButton);
        window.draw(openText);

        window.draw(clearButton);
        window.draw(clearText);

        window.draw(textDisplay);

        window.display();
    }

    return 0;
}
