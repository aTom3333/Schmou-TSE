#include "Partie.h"
#include "ProjTest.h"

Partie::Partie()
{
}

Partie::~Partie()
{
}

void Partie::jeu(sf::RenderWindow & window)
{
	ProjTest proj_test;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		proj_test.gestion(window);
		window.display();
	}
}
