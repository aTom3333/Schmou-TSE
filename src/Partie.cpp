#include "Partie.h"

Partie::Partie()
{
}

Partie::~Partie()
{
}

void Partie::jeu(sf::RenderWindow * window)
{
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}

		window->clear();
		window->display();
	}
}
