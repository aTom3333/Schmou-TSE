#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "Entite.h"
#include "Collision.h"


// Code minimal
int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!", sf::Style::Default, settings);
	sf::CircleShape cercle(50.f);
	cercle.setFillColor(sf::Color::Green);
	cercle.setPosition(100, 100);
	cercle.setOrigin(50, 50);

	sf::CircleShape c(26);
	c.setOrigin(26, 26);
	c.setPosition(150, 100);
	c.setFillColor(sf::Color::Blue);

	if(collision(cercle, c))
		std::cout << "Collision !" << std::endl;


	sf::ConvexShape triangle(3);
	double cote = 170;
	triangle.setOrigin(cote/2, sqrt(3)/2 * cote * 2/3);
	triangle.setPoint(0, {0, sqrt(3)/2 * cote});
	triangle.setPoint(1, {cote/2, 0});
	triangle.setPoint(2, {cote, sqrt(3)/2 * cote});
	triangle.setPosition(500, 200);
	triangle.setFillColor(sf::Color::Red);
	triangle.setRotation(60);

	sf::CircleShape origine(2);
	origine.setOrigin(2, 2);
	origine.setFillColor(sf::Color::Black);
	origine.setPosition(triangle.getPosition());

	Entite e1;
	e1.forme_.push_back(&triangle);

	sf::Image map;
	map.create(800, 800, sf::Color(0, 0, 0, 127));
	for(int  i = 0; i < 800; i++)
	{
		for(int j = 0; j < 800; ++j)
		{
			c.setPosition(i, j);
			if(collision(c, triangle))
				map.setPixel(i, j, sf::Color(255, 255, 255, 127));
		}
	}

	sf::Texture t;
	t.create(800, 800);
	t.update(map);
	sf::Sprite s;
	s.setTexture(t);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed)
			{
				auto pos = sf::Mouse::getPosition(window);
				std::cout << pos.x << " " << pos.y << std::endl;
				c.setPosition(pos.x, pos.y);
				if(collision(triangle, c))
					std::cout << "Collision !" << std::endl;
				else
					std::cout << "Pas de collision..." << std::endl;
			}
		}

		window.clear(sf::Color::White);
		window.draw(cercle);
		window.draw(*e1.forme_[0]);
		window.draw(c);
		window.draw(s);
		window.draw(origine);
		window.display();
	}

	return 0;
}

