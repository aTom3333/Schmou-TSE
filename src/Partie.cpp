#include "Partie.h"
#include "Projectiles/_projectiles.h"
#include "Capacites/_Capacites.h"
#include "Vaisseau/_vaisseaux.h"
#include "Interface/bindings.h"


Partie::Partie(sf::RenderWindow& window) : window_{window}, input_(window)
{
	if (!font_.loadFromFile("../../rc/Font/hemi.ttf"))
	{
		std::cout << "Impossible de charger la police" << std::endl;
	}

	set_keyboard_binding(input_);
}

Partie::~Partie()
{
}



void Partie::testProjTest()
{
	sf::Clock clock;

	


	VaisseauTest *vaisseautest = new VaisseauTest;
	VaisseauEclaireur *vaiseauEclaireurL = new VaisseauEclaireur(0, 0, LINEAIRE, 1, 0.5);
	VaisseauEclaireur *vaiseauEclaireurP = new VaisseauEclaireur(1000, 0, PARABOLIQUE, -1, 500, 500);
	VaisseauEclaireur *vaiseauEclaireurS = new VaisseauEclaireur(1000, 0, SINUS, -1, 300, 100, -.7);

	vaisseaux_.push_back(vaisseautest);
	vaisseaux_.push_back(vaiseauEclaireurL);
	vaisseaux_.push_back(vaiseauEclaireurP);
	vaisseaux_.push_back(vaiseauEclaireurS);

	while (window_.isOpen())
	{
		// Gestion  des evenement qui n'est pas bien implémentée ! ah si thomas est passé par là :o 
		sf::Event event;
		while (window_.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window_.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window_.close();
		}

		auto t_ecoule = clock.restart();
		
		// Efface l'écran
		window_.clear();

		//Gestion des vaisseaux
		for (int i = 0; i < vaisseaux_.size(); i++)
		{
			vaisseaux_[i]->gestionCapacite(projectiles_, t_ecoule);
			vaisseaux_[i]->gestion(window_, t_ecoule, input_);
		}

		// Gestion des projectiles_
		for (int i = 0; i < projectiles_.size(); i++)
			projectiles_[i]->gestion(window_);

		// Collision moisie
		//testCollision(projectiles_);
		for (int i = 0; i < projectiles_.size(); i++) {
			if (projectiles_[i]->estDehors())
			{
				delete projectiles_[i];
				projectiles_[i] = projectiles_[projectiles_.size() - 1];
				projectiles_.pop_back();
				i--;
			}
			else {
				for (int j = 0; j < i; j++) {

					if (collision(*projectiles_[i], *projectiles_[j])) {
						projectiles_[i]->agit(*projectiles_[j]);
					}
				}
			}
		}

		// Mise à jour de l'écran
		window_.display();

		sf::sleep(sf::milliseconds(10));
	}
}

//test vaisseau piou piou de pierre
void Partie::testVaisseauTest() {
	//déclarations
	VaisseauTest vaisseautest;
	sf::Clock clock;
	float t_ecoule;

	while (window_.isOpen())
	{
		//boucle de base 
			sf::Event event;
			while (window_.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window_.close();
			}

		//maj début de boucle
			t_ecoule = clock.restart().asMilliseconds();
			window_.clear();

		//code
			//vaisseautest.gestion(window_, t_ecoule);

		//maj fin de boucle
			window_.display();
			sf::sleep(sf::milliseconds(10));
	}
}

// TODO A refaire !!!!

void Partie::testCollision(std::vector<Projectile*> &projectiles_)
{
	if (projectiles_.size() != 0)
	{
		for (int i = 0; i < projectiles_.size() - 1; i++)
		{
			if (projectiles_[i]->estDehors())
			{
				delete projectiles_[i];
				projectiles_[i] = projectiles_[projectiles_.size() - 1];
				projectiles_.pop_back();
			}
			else
			{
				for (int j = i + 1; j < projectiles_.size(); j++)
				{
					if (collision(*projectiles_[i], *projectiles_[j]))
					{
						int r = rand() % 2 == 0 ? i : j;
						delete projectiles_[r];
						projectiles_[r] = projectiles_[projectiles_.size() - 1];
						projectiles_.pop_back();
						i--;
						break;
					}
				}
			}
			
		}
	}

}
