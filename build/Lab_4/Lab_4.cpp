#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <array_list.h>
#include <iostream>

class TextCircle
{
private:
	sf::Text my_text;
	sf::CircleShape my_circle;


public:
	TextCircle(sf::Font& the_font) : my_text(the_font)  // We HAVE to use this syntax to pass
	{								// the required parameter to my_text's constructor
		//my_text(the_font);		// Nice thought, but too late.
	}

	void set_position(float x, float y)
	{
		my_text.setPosition(sf::Vector2f(x, y));
		my_circle.setPosition(sf::Vector2f(x, y));
	}

	void set_text(std::string s)
	{
		my_text.setString(s);
		// Adjust circle radius to fit??
	}

	void draw(sf::RenderWindow& rw)
	{
		rw.draw(my_text);
		rw.draw(my_circle);
	}
};


int main(int argc, char** argv)
{
	
	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "ALBRO'S Lab4 Solution");
	sf::CircleShape test_circle(100.0f);
	ssuds::ArrayList<float> circle_xlist;
	ssuds::ArrayList<float> circle_ylist;

	ssuds::ArrayList<float> bullet_ylist;
	ssuds::ArrayList<float> bullet_xlist;

	ssuds::ArrayList<std::string> circle_strings;
	test_circle.setFillColor(sf::Color(200, 255, 100, 255));
	test_circle.setPosition(sf::Vector2f(150.0f, 10.0f));
	test_circle.setOrigin(sf::Vector2f(100.0f, 100.0f));

	


	
	while (window.isOpen())
	{
		
		while (const std::optional event = window.pollEvent())
		{
			
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
			else if (const sf::Event::KeyPressed* keyEvt = event->getIf<sf::Event::KeyPressed>())
			{
				if (keyEvt->code == sf::Keyboard::Key::Escape)
				{
					window.close();
				}
			}
			else if (const sf::Event::MouseButtonPressed* buttonEvt =
				event->getIf<sf::Event::MouseButtonPressed>())
			{
				if (buttonEvt->button == sf::Mouse::Button::Left)
				{
				}
			}

		}

		window.clear();
		window.draw(test_circle);
		////for (int i = 0; i < circle_xlist.size(); i++)
		//{
			//float x = circle_xlist[i];
			//float y = circle_ylist[i];
			//std::string s = circle_strings[i];
		//}
		//for (int i = 0; i < circle_ylist.size(); i++)
		//{
			//if (circle_ylist[i] >= 600)
			//{
				//circle_ylist.remove(i);
				//circle_xlist.remove(i);
			//}
		//}

		window.display();// Shows our drawings
	}
	return 0;
}