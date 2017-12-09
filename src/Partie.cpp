#include "Partie.h"
#include "_projectiles.h"
#include "_attaques.h"
#include "ProjTest.h"
#include "VaisseauTest.h"



Partie::Partie()
{
	if (!font_.loadFromFile("../../rc/Font/hemi.ttf"))
	{
		std::cout << "Impossible de charger la police" << std::endl;
	}
}

Partie::~Partie()
{
}

void Partie::testProjTest(sf::RenderWindow & window)
{
	AtkTest atkTest;
	std::vector<Projectile *> projectiles;
	sf::Clock clock;
	sf::Text afficheAtk;

	afficheAtk.setFont(font_);
	afficheAtk.setCharacterSize(20);
	afficheAtk.setFillColor(sf::Color::White);
	afficheAtk.setPosition(0, 0);

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

		std::string txt;
		if(atkTest.getCooldown() - atkTest.getTime() != 0)
			txt = atkTest.getNom() + " - " + std::to_string(atkTest.getCooldown() - atkTest.getTime());
		else
			txt = atkTest.getNom() + " - " + "Prêt";
		afficheAtk.setString(txt);
		window.draw(afficheAtk);
		window.display();

		sf::sleep(sf::milliseconds(10));
	}
}

//test vaisseau piou piou de pierre
void Partie::testVaisseauTest(sf::RenderWindow & window) {
	//déclarations
	VaisseauTest vaisseautest;
	sf::Clock clock;
	float t_ecoule;

	while (window.isOpen())
	{
		//boucle de base 
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

		//maj début de boucle
			t_ecoule = clock.restart().asMilliseconds();
			window.clear();

		//code
			vaisseautest.gestion(window);

		//maj fin de boucle
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
