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
	VaisseauTest vaisseautest;
	VaisseauEclaireur vaiseauEclaireurL(0, 0, LINEAIRE,1, 0.5);
	VaisseauEclaireur vaiseauEclaireurP(1000, 0, PARABOLIQUE,-1, 500, 500);
	VaisseauEclaireur vaiseauEclaireurS(1000, 0, SINUS,-1, 300, 100, -.7);

	sf::Text afficheAtk;
	int attaqueEnCours = 0;

	// Initialisation du texte (Nom capacité + Cooldown)
	afficheAtk.setFont(font_);
	afficheAtk.setCharacterSize(20);
	afficheAtk.setFillColor(sf::Color::White);
	afficheAtk.setPosition(0, 0);

	// Test Vecteur d'attaque
	CapTest *temp1 = new CapTest();
	capacites_.push_back(temp1);

	CapPiou *temp2 = new CapPiou();
	capacites_.push_back(temp2);

	CapDash *temp3 = new CapDash();
	capacites_.push_back(temp3);

	while (window_.isOpen())
	{
		// Gestion  des evenement qui n'est pas bien implémentée ! ah si thomas est passé par là :o 
		sf::Event event;
		while (window_.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window_.close();

			// Si la touche W est activé
			if (input_.action(0))
			{
				// Lance la compétance à la position du vaisseau allié
				sf::Vector2f posVaisseau = vaisseautest.getPosition();
				capacites_[attaqueEnCours]->utiliser(posVaisseau.x, posVaisseau.y);
			}
			// Si la touche X est activé
			if (input_.action(1))
			{
				// Changement d'attaque
				attaqueEnCours++;
				if (attaqueEnCours >= capacites_.size())
					attaqueEnCours = 0;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window_.close();
		}

		auto t_ecoule = clock.restart();
		
		// Efface l'écran
		window_.clear();

		// Gestion du vaisseau
        vaisseautest.move(input_.move(vaisseautest.getvit(), t_ecoule));
		vaisseautest.gestion(window_, t_ecoule.asMilliseconds());


		vaiseauEclaireurP.gestion(window_, t_ecoule.asMilliseconds());
		vaiseauEclaireurL.gestion(window_, t_ecoule.asMilliseconds());
		vaiseauEclaireurS.gestion(window_, t_ecoule.asMilliseconds());

		// Gestion des capacites_
		for(int i = 0; i < capacites_.size(); i++)
			capacites_[i]->actualiser(projectiles_, vaisseautest, t_ecoule.asMilliseconds());

		// Gestion des projectiles_
		for(int i = 0; i < projectiles_.size(); i++)
			projectiles_[i]->gestion(window_);

		// Collision moisie
		testCollision(projectiles_);
		for (int i = 0; i < projectiles_.size(); i++) {
			if (projectiles_[i]->estDehors())
			{
				delete projectiles_[i];
				projectiles_[i] = projectiles_[projectiles_.size() - 1];
				projectiles_.pop_back();
			}
			for (int j = 0; j < projectiles_.size(); j++) {
				
				if (collision(*projectiles_[i], *projectiles_[j])) {
					projectiles_[i]->agit(*projectiles_[j]);
				}
			}
		}


		// Affichage attaque en cours
		std::string txt;
		if(capacites_[attaqueEnCours]->getCooldown() - capacites_[attaqueEnCours]->getTime() > 0)
			txt = capacites_[attaqueEnCours]->getNom() + " - " + std::to_string((int)(capacites_[attaqueEnCours]->getCooldown() - capacites_[attaqueEnCours]->getTime()));
		else
			txt = capacites_[attaqueEnCours]->getNom() + " - " + "Pret";
		afficheAtk.setString(txt);
		window_.draw(afficheAtk);

		// Mise à jour de l'écran
		window_.display();

		sf::sleep(sf::milliseconds(10));
	}

	for (int i = 0; i < capacites_.size(); i++)
		delete capacites_[i];
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
			vaisseautest.gestion(window_, t_ecoule);

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
