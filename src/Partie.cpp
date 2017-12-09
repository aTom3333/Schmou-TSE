#include "Partie.h"
#include "_projectiles.h"
#include "_attaques.h"



Partie::Partie()
{
}

Partie::~Partie()
{
}

void Partie::jeu(sf::RenderWindow & window)
{
	AtkTest atkTest;
	std::vector<Projectile *> projectiles;
	sf::Clock clock;

	while (window.isOpen())  
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				// récupération de la position de la souris dans la fenêtre
				sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
				// conversion en coordonnées "monde"
				sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

				atkTest.utiliser(worldPos.x, worldPos.y);
			}
		}

		float t_ecoule = clock.restart().asMilliseconds();
		
		window.clear();

		// Gestion des attaques
		atkTest.actualiser(projectiles);

		for(int i = 0; i < projectiles.size(); i++)
			projectiles[i]->gestion(window);

		testCollision(projectiles);

		window.display();

		sf::sleep(sf::milliseconds(10));
	}
}

// TODO A refaire !!!!

void Partie::testCollision(std::vector<Projectile*> &projectiles)
{
	if (projectiles.size() != 0)
	{
		for (int i = 0; i < projectiles.size() - 1; i++)
		{
			for (int j = i + 1; j < projectiles.size(); j++)
			{
				if (collision(*projectiles[i], *projectiles[j]))
				{
					int r = rand() % 2 == 0 ? i : j;
					delete projectiles[r];
					projectiles[r] = projectiles[projectiles.size() - 1];
					projectiles.pop_back();
					i--;
					break;
				}
			}
		}
	}

}
