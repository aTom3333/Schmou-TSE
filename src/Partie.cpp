#include "Partie.h"
#include "Projectiles/_projectiles.h"
#include "Capacites/_Capacites.h"
#include "Projectiles/ProjTest.h"
#include "Vaisseau/VaisseauTest.h"




Partie::Partie(sf::RenderWindow& window) : window_{window}, input(window)
{
	if (!font_.loadFromFile("../../rc/Font/hemi.ttf"))
	{
		std::cout << "Impossible de charger la police" << std::endl;
	}
}

Partie::~Partie()
{
}



void Partie::testProjTest()
{
	std::vector<Capacite*> attaques;
	std::vector<Projectile *> projectiles;
	sf::Clock clock;
	VaisseauTest vaisseautest;
	sf::Text afficheAtk;
	int attaqueEnCours = 0;

	// Initialisation du texte (Nom capacité + Cooldown)
	afficheAtk.setFont(font_);
	afficheAtk.setCharacterSize(20);
	afficheAtk.setFillColor(sf::Color::White);
	afficheAtk.setPosition(0, 0);

	// Test Vecteur d'attaque
	CapTest *temp1 = new CapTest();
	attaques.push_back(temp1);

	CapPiou *temp2 = new CapPiou();
	attaques.push_back(temp2);

	CapDash *temp3 = new CapDash();
	attaques.push_back(temp3);

	while (window_.isOpen())
	{
		// Gestion nulle des evenement
		sf::Event event;
		while (window_.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window_.close();

			// Si la touche W est activé
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				// Lance la compétance à la postion du vaisseau allié
				sf::Vector2f worldPos = vaisseautest.getPosition();
				attaques[attaqueEnCours]->utiliser(worldPos.x, worldPos.y);
			}
			// Si la touche X est activé
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
			{
				// Changement d'attaque
				attaqueEnCours++;
				if (attaqueEnCours >= attaques.size())
					attaqueEnCours = 0;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window_.close();
		}

		auto t_ecoule = clock.restart();
		
		// Efface l'écran
		window_.clear();

		// Gestion du vaisseau
        vaisseautest.move(input.move(vaisseautest.getvit(), t_ecoule));
		vaisseautest.gestion(window_);

		// Gestion des attaques
		for(int i = 0; i < attaques.size(); i++)
			attaques[i]->actualiser(projectiles, &vaisseautest);

		// Gestion des projectiles
		for(int i = 0; i < projectiles.size(); i++)
			projectiles[i]->gestion(window_);

		// Collision moisie
		testCollision(projectiles);


		// Affichage attaque en cours
		std::string txt;
		if(attaques[attaqueEnCours]->getCooldown() - attaques[attaqueEnCours]->getTime() != 0)
			txt = attaques[attaqueEnCours]->getNom() + " - " + std::to_string(attaques[attaqueEnCours]->getCooldown() - attaques[attaqueEnCours]->getTime());
		else
			txt = attaques[attaqueEnCours]->getNom() + " - " + "Prêt";
		afficheAtk.setString(txt);
		window_.draw(afficheAtk);

		// Mise à jour de l'écran
		window_.display();

		sf::sleep(sf::milliseconds(10));
	}

	for (int i = 0; i < attaques.size(); i++)
		delete attaques[i];
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
			vaisseautest.gestion(window_);

		//maj fin de boucle
			window_.display();
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
			if (projectiles[i]->estDehors())
			{
				delete projectiles[i];
				projectiles[i] = projectiles[projectiles.size() - 1];
				projectiles.pop_back();
			}
			else
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

}
