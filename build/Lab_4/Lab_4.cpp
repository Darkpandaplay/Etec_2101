#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

int main(int argc, char** argv)
{
    sf::RenderWindow window(sf::VideoMode({ 800,600 }), "Albro Lab4 Solution");
    sf::CircleShape test_circle(100.0f);
    test_circle.setFillColor(sf::Color::Green);
    float dy = 5.5;
    test_circle.setPosition(sf::Vector2f(100.0f, 10.0f));
    sf::FloatRect boundingBox = test_circle.getGlobalBounds();
    sf::Vector2f point = sf::Vector2f(150.0f, 250.0f);

    while (window.isOpen())
    {
        test_circle.move({ 0.f, 0.1f });
        if (boundingBox.contains(point))
        {
            test_circle.move({ 0.f, -1.0f });
        }
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