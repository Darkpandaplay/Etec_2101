#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <array_list.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <random>

//Reader Class
class WordReader
{
private:
	size_t file_len;
	std::ifstream fp;

public:
	WordReader();

	~WordReader();

	std::string extracto();

};

WordReader::WordReader()
{
	fp.open("../../media/american-words.txt", std::ios::binary);
	fp.seekg(0, std::ios::end);
	file_len = fp.tellg();
}

WordReader::~WordReader()
{
	fp.close();
}

std::string WordReader::extracto()
{
	int rando = std::rand() % file_len - 1;
	fp.seekg(rando, std::ios::beg);
	fp.seekg(-1, std::ios::cur);

	char boo = fp.peek();
	while (boo == '11')
	{
		fp.seekg(0, std::ios::cur);
		boo = fp.peek();
	}
	std::string read_word;
	std::getline(fp, read_word);
	return read_word;
}
// End of WordReader Class Begining of TextCircle Class
class TextCircle
{
private:
	sf::Text my_text;
	sf::CircleShape my_circle;
	float size_circ;

public:
	TextCircle(sf::Font& the_font,float size) : my_text(the_font)  // Variable used to make the size of the Circle wich is then used at the setting of the orgin
	{							
		my_circle = sf::CircleShape(size);
		my_circle.setOrigin(sf::Vector2(size, size));
		my_circle.setFillColor(sf::Color(0, 35, 225));
		size_circ = size;
	}

	void set_position(float x, float y)
	{
		my_text.setPosition(sf::Vector2f(x, y));
		my_circle.setPosition(sf::Vector2f(x, y));
	}

	void set_text(std::string s)
	{
		my_text.setString(s);
		my_text.setFillColor(sf::Color(0, 45, 5));
		sf::FloatRect text_bounds = my_text.getLocalBounds();
		sf::Vector2f text_size = text_bounds.size;
		my_text.setCharacterSize(size_circ / 3);
		my_text.setOrigin(sf::Vector2f(text_size.x / 4.0f, text_size.y / 3.0f));
	}

	void draw(sf::RenderWindow& rw)
	{
		rw.draw(my_circle);
		rw.draw(my_text);
	}
};


//MAIN LOOP

int main(int argc, char** argv)
{
	
	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "ALBRO'S Lab4 Solution");

	ssuds::ArrayList<float> circle_xlist;
	ssuds::ArrayList<float> circle_ylist;
	ssuds::ArrayList<float> circle_speed;
	ssuds::ArrayList<std::string> circle_strings;

	ssuds::ArrayList<float> bullet_ylist;
	ssuds::ArrayList<float> bullet_xlist;
	ssuds::ArrayList<float> bullet_dx;
	ssuds::ArrayList<float> bullet_dy;

	sf::Clock Clock1;
	sf::Clock Clock2;

	sf::Texture background_texture("../../media/background.png");
	sf::Sprite background_sprite(background_texture);
	background_sprite.setScale({ 4, 2.75 });

	sf::Font my_font("../../media/static/Oswald-Light.ttf");
	ssuds::ArrayList<float> circle_sizes;
	WordReader reader;

	
	while (window.isOpen())
	{
		window.clear();
		window.draw(background_sprite);
		
		if (Clock1.getElapsedTime().asSeconds() >= 1.0f)
		{
			circle_xlist.append(20 + rand() % 760);
			circle_ylist.append(0);
			circle_sizes.append(30 + std::rand() % 21);
			circle_speed.append(50 + std::rand() % 51);
			std::string temp = reader.extracto();
			circle_strings.append(temp);
			Clock1.restart();
		}
		float deltaT = Clock2.getElapsedTime().asSeconds();
		Clock2.restart();
		
		//Circ shenanigans
		for (int i = 0; i < circle_xlist.size(); i++)
		{
			float x = circle_xlist[i];
			float move = circle_speed[i] * deltaT;
			float y = circle_ylist[i] += move;
			float size = circle_sizes[i];
			std::string text = circle_strings[i];
			if (y >= (600 + size))
			{
				circle_xlist.remove(i);
				circle_ylist.remove(i);
				circle_sizes.remove(i);
				circle_speed.remove(i);
				circle_strings.remove(i);
			}
			else
			{
				TextCircle temp(my_font, size);
				temp.set_text(text);
				temp.set_position(x, y);
				temp.draw(window);
			}
		}
		
		//Bullet shenanigans
		for (int i = 0; i < bullet_ylist.size(); i++)
		{
			for (int cir = 0; cir < circle_xlist.size(); cir++)
			{
				float dx = bullet_xlist[i] - circle_xlist[cir];
				float dy = bullet_ylist[i] - circle_ylist[cir];
				float distance = std::sqrt(dx * dx + dy * dy);
				//Never thought old yost python code would be so useful (JK)

				if (distance < 10 + circle_sizes[cir])
				{
					circle_xlist[cir] = 8000;
					circle_ylist[cir] = 6000;
					bullet_xlist[i] = 8000;
					bullet_ylist[i] = 6000;
					break;
				}
			}

			float velx = bullet_dx[i] * 150 * deltaT;
			float vely = bullet_dy[i] * 150 * deltaT;

			float x = bullet_xlist[i] += velx;
			float y = bullet_ylist[i] += vely;
			float size = 10.0f;
			if (y >= (600 + size) || y <= 0 + size || x >= 800 + size || x <= 0)
			{
				bullet_xlist.remove(i);
				bullet_ylist.remove(i);
				bullet_dy.remove(i);
				bullet_dx.remove(i);
			}
			else
			{
				sf::CircleShape temp(size);
				temp.setOrigin(sf::Vector2f(size, size));
				temp.setPosition(sf::Vector2(x, y));
				temp.setFillColor(sf::Color(0, 50, 120));
				window.draw(temp);
			}
		}

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
					sf::Vector2f temp_pos(buttonEvt->position.x, buttonEvt->position.y);

					bullet_xlist.append(400.0f);
					bullet_ylist.append(555.0f);

					float dx = buttonEvt->position.x - 400;
					float dy = buttonEvt->position.y - 550;
					float mag = std::sqrt(dx * dx + dy * dy);
					if (mag != 0.0f) {
						dx = dx / mag;
						dy = dy / mag;
					}
					bullet_dx.append(dx);
					bullet_dy.append(dy);
				}
			}
		}
		window.display();// Shows our drawings
	}
	return 0;
}