#include <SFML/Graphics.hpp>
#include <cmath>
#include <ctime>
#include <iostream>
#include "constantes.h"
#include "Entite.h"
#include "Collision.h"
#include "Partie.h"


// Code minimal
int main()
{
	// Code propre 

	sf::RenderWindow window(sf::VideoMode(ECRAN_L,ECRAN_H), "Schmou'TSE", sf::Style::Fullscreen);
	Partie partie;

	srand(time(nullptr));

	partie.testProjTest(window); ///le truc que Cyril avait tapé jeudi 7 en club
	
	//partie.testVaisseauTest(window); ///un vaisseau que pierre a testé



	//Bordel de Thomas 
	///<attention très bordélique
	/*
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!", sf::Style::Default, settings);
	sf::CircleShape cercle(50.f);
	cercle.setFillColor(sf::Color::Green);
	cercle.setPosition(300, 100);
	cercle.setOrigin(0, 0);
	cercle.setRotation(90);
	cercle.setScale(2.5, 2.5);

	sf::CircleShape c(26);
	c.setOrigin(26, 26);
	c.setPosition(500, 200);
	c.setFillColor(sf::Color::Blue);

	sf::RectangleShape r({100, 200});
	r.setPosition(420, 460);
	r.setFillColor(sf::Color::Magenta);
	r.rotate(30);


	sf::ConvexShape triangle(3);
	double cote = 170;
	triangle.setOrigin(cote/2, sqrt(3)/2 * cote * 2/3);
	triangle.setPoint(0, {0, sqrt(3)/2 * cote});
	triangle.setPoint(2, {cote/2, 0});
	triangle.setPoint(1, {cote, sqrt(3)/2 * cote});
	triangle.setPosition(500, 200);
	triangle.setFillColor(sf::Color::Red);
	triangle.setScale(1.5, 2.5);
	triangle.setRotation(60);

	if(collision(triangle, c))
		std::cout << "Collision !" << std::endl;

	sf::CircleShape origine(2);
	origine.setOrigin(2, 2);
	origine.setFillColor(sf::Color::Black);
	origine.setPosition(c.getPosition());

	sf::Image masque;
	masque.create(800, 800, sf::Color(0, 0, 0, 127));
	for(int  i = 0; i < 800; i++)
	{
		for(int j = 0; j < 800; ++j)
		{
			c.setPosition(i, j);
			if(collision(c, triangle))
				masque.setPixel(i, j, sf::Color(255, 255, 255, 127));
		}
	}

	sf::Texture t;
	t.create(800, 800);
	t.update(masque);
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
				c.setPosition(pos.x, pos.y);
				if(collision(r, c))
					std::cout << "Collision !" << std::endl;
				else
					std::cout << "Pas de collision..." << std::endl;
			}
		}

		window.clear(sf::Color::White);
		window.draw(cercle);
		window.draw(triangle);
		window.draw(r);
		window.draw(c);
		window.draw(s);
		window.draw(origine);
		window.display();
	}*/

	return 0;
}

