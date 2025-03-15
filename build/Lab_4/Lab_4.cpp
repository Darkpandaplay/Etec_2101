#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

int main(int argc, char** argv)
{
    sf::RenderWindow window(sf::VideoMode({ 800,600 }), "Albro Lab4 Solution");
    sf::CircleShape test_circle(100.0f);
    test_circle.setFillColor(sf::Color::Green);
    test_circle.setPosition(sf::Vector2f(10.0f, 10.0f));

    while (window.isOpen())
    {
        //Iput-handling
        while (const std::optional event = window.pollEvent())
        {

        }
        //Drawing
        window.clear();
        window.draw(test_circle);
        window.display();
    }
    return 0;

}