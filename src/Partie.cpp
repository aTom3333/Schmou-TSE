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
	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		float t_ecoule = clock.restart().asMilliseconds();
		
		window.clear();
		proj_test.gestion(window);
		window.display();

		sf::sleep(sf::milliseconds(10));
	}
}
