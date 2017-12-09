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
	std::vector<Projectile *> proj_test;
	sf::Clock clock;

	for (int i = 0; i < 20; i++)
	{
		ProjTest *newProj = new ProjTest;
		proj_test.push_back(newProj);
	}

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
		for(int i = 0; i < proj_test.size(); i++)
			proj_test[i]->gestion(window);

		for (int i = 0; i < proj_test.size() - 1; i++)
		{
			for (int j = i + 1; j < proj_test.size(); j++)
			{
				if (collision(*proj_test[i], *proj_test[j]))
				{
					std::cout << "bouh ! " << std::endl;
					int r = rand() % 2 == 0 ? i : j;
					delete proj_test[r];
					proj_test[r] = proj_test[proj_test.size() - 1];
					proj_test.pop_back();
					i--;
					break;
				}
			}
		}

		window.display();

		sf::sleep(sf::milliseconds(10));
	}
}

// TODO A refaire !!!!

void Partie::testCollision(std::vector<Projectile*> projectiles)
{
	for (int i = 0; i < projectiles.size() - 1; i++)
	{
		for (int j = i+1; j < projectiles.size(); j++)
		{
			if (collision(*projectiles[i], *projectiles[j]))
			{
				int r = rand() % 2 == 0 ? i : j;
				projectiles.erase(projectiles.begin() + r);
			}
		}
	}
		

}
