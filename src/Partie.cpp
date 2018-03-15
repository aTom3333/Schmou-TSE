#include "Partie.h"
#include "Projectiles/_projectiles.h"
#include "Capacites/_Capacites.h"
#include "Vaisseau/_vaisseaux.h"
#include "Interface/bindings.h"
#include "Pattern/Vague.h"

Partie::Partie(sf::RenderWindow& window, Input::Media media, bool afficheHUD, bool avecPattern) : window_{window}, input_(window, media), afficheHUD_{afficheHUD}, avecPattern_{avecPattern}
{
	if (!font_.loadFromFile("../../rc/Font/hemi.ttf"))
	{
		std::cout << "Impossible de charger la police" << std::endl;
	}
	
	if (media == Input::Media::Mouse)set_mouse_default_binding(input_);
	if (media == Input::Media::Keyboard)set_keyboard_default_binding(input_);
	if (media == Input::Media::Joypad)set_joypad_default_binding(input_);

}

Partie::~Partie()
{
	for(unsigned int i = 0; i < vaisseaux_.size(); i++)
		delete vaisseaux_[i];
	for(unsigned int i = 0; i < projectiles_.size(); i++)
		delete projectiles_[i];
}

void Partie::testPartie()
{
	//horloge
	sf::Clock clock;

	//Joueur
	VaisseauTest *vaisseautest = new VaisseauTest;
	vaisseautest->setequipe_(JOUEUR);
	vaisseaux_.push_back(vaisseautest);
	vaisseaux_[0]->setPosition({ 500,700 });

	//init patterns
	if (avecPattern_) {
		initPatternTest();
	}

	// Modifie la vitesse du jeu (debug)
	timeSpeed_ = 1;

    // Déplacer la souris à la position du vaisseau
    auto pos = vaisseaux_[0]->getPosition();
    pos.x += 32;
    pos.y += 32;
    sf::Mouse::setPosition(window_.mapCoordsToPixel(pos), window_);

	hud_.init(vaisseaux_[0]);

	while (window_.isOpen())
	{
		// Gestion  des évènements 
		sf::Event event;
		while (window_.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Delete))
				//TODO PG 07-03-2018 j'ai mis Suppr pour fermer temporairement
				window_.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
			{
				if (timeSpeed_ < 20)
				{
					timeSpeed_ += 0.1;
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
			{
				if (timeSpeed_ >= 0.1)
				{
					timeSpeed_ -= 0.1;
				}
				else if (timeSpeed_ > 0.01)
				{
					timeSpeed_ -= 0.01;
				}
			}
		}
		timeSpeed_ = 0.1;

		//gestion temps
		auto t_ecoule = clock.restart();
		t_ecoule = t_ecoule * (float)timeSpeed_;

		// Efface l'écran
		window_.clear();

		// Gestion des vagues
		if (avecPattern_)
		{
			for(unsigned int i = 0; i < pattern_.size(); i++)
				pattern_[i].gestion(vaisseaux_, t_ecoule);
		}

		//Gestion des vaisseaux
		for(unsigned int i = 0; i < vaisseaux_.size(); i++)
		{
			vaisseaux_[i]->regen(t_ecoule);
			vaisseaux_[i]->gestionCapacite(projectiles_, t_ecoule);
			vaisseaux_[i]->gestion(window_, t_ecoule, input_);
		}

		// Gestion des projectiles_
		for(unsigned int i = 0; i < projectiles_.size(); i++)
		{
			projectiles_[i]->regen(t_ecoule);
			projectiles_[i]->gestion(window_, t_ecoule);
		}			

		// Gestion des collisions
		collisionProjectile(); //le code est plus bas
		collisionVaisseaux();

		// Affichage de l'ATH
		if (afficheHUD_)
		{
			hud_.gestion(vaisseaux_[0]);
			hud_.draw(window_, vaisseaux_[0], afficheHUD_);
		}
			

		// Mise à jour de l'écran
		window_.display();

		window_.setTitle("Schmou'TSE - Vitesse de jeu : " + std::to_string(timeSpeed_));
		sf::sleep(sf::milliseconds(10));
	}
}

void Partie::collisionProjectile()
{
	/*std::vector<Entite*> allEntite;
	allEntite.insert(projectiles_.begin(), vaisseaux_.begin(), vaisseaux_.end());*/
	unsigned int n = projectiles_.size() + vaisseaux_.size();
	Entite **allEntite = new Entite*[projectiles_.size() + vaisseaux_.size()];

	for(unsigned int i = 0; i < projectiles_.size(); i++)
		allEntite[i] = projectiles_[i];
	for(unsigned int i = projectiles_.size(); i < n; i++)
		allEntite[i] = vaisseaux_[i - projectiles_.size()];


	if (projectiles_.size() != 0)
	{
		for(unsigned int i = 0; i < projectiles_.size(); i++)
		{
			// Si le projectile est dehors
			if (projectiles_[i]->estDehors())
				projectiles_[i]->destruction();
			else
			{
				// Collision avec une autre entite
				for(unsigned int j = i + 1; j < n; j++)
				{
					if (collision(*allEntite[i], *allEntite[j]))
					{
						allEntite[i]->agit(*allEntite[j]);
						allEntite[j]->agit(*allEntite[i]);
					}
						
				}
			}		
		}
	}
	deleteProjectileDetruit();
	deleteVaisseauDetruit();
	delete[] allEntite;
}

void Partie::collisionVaisseaux()
{
	if (vaisseaux_.size() != 0)
	{
		for (unsigned int i = 0; i < vaisseaux_.size() - 1; i++)
		{
			// Si le vaisseau est dehors
			if (vaisseaux_[i]->estDehors())
			{
				vaisseaux_[i]->destruction();				
			}
			else
			{
				for (unsigned int j = i + 1; j < vaisseaux_.size(); j++)
				{
					if (collision(*vaisseaux_[i], *vaisseaux_[j]))
					{
						vaisseaux_[j]->agit(*vaisseaux_[i]);
						vaisseaux_[i]->agit(*vaisseaux_[j]);
					}
				}
			}			
		}
	}
	deleteVaisseauDetruit();
}

void Partie::deleteProjectileDetruit()
{
	for(unsigned int i = 0; i < projectiles_.size(); i++)
	{
		if (projectiles_[i]->estDetruit())
		{
			delete projectiles_[i];
			projectiles_[i] = projectiles_[projectiles_.size() - 1];
			projectiles_.pop_back();
		}
	}
}

void Partie::deleteVaisseauDetruit()
{
	for(unsigned int i = 0; i < vaisseaux_.size(); i++)
	{
		if (vaisseaux_[i]->estDetruit())
		{
			if (i == 0)
				afficheHUD_ = false;
			delete vaisseaux_[i];
			vaisseaux_[i] = vaisseaux_[vaisseaux_.size() - 1];
			vaisseaux_.pop_back();
		}
	}
}

void Partie::initPatternTest()
{
	Vague v1(0), v2(5000), v3(10000), v4(15000), v5(10000);

	/*VaisseauEclaireur *vaiseauEclaireurL = new VaisseauEclaireur(0, 0, LINEAIRE, 1, 0.5);
	VaisseauEclaireur *vaiseauEclaireurP = new VaisseauEclaireur(1000, 0, PARABOLIQUE, -1, 500, 500);
	VaisseauEclaireur *vaiseauEclaireurS = new VaisseauEclaireur(1000, 0, SINUS, -1, 300, 100, -.7);*/

	v1.ajouterVaisseau(0, new VaisseauEclaireur(0, 0, LINEAIRE, 1, 0.5));
	v1.ajouterVaisseau(400, new VaisseauEclaireur(0, 0, LINEAIRE, 1, 0.5));
	v1.ajouterVaisseau(800, new VaisseauEclaireur(0, 0, LINEAIRE, 1, 0.5));
	v1.ajouterVaisseau(1200, new VaisseauEclaireur(0, 0, LINEAIRE, 1, 0.5));
	v1.ajouterVaisseau(1600, new VaisseauEclaireur(0, 0, LINEAIRE, 1, 0.5));

	v2.ajouterVaisseau(0, new VaisseauEclaireur(1000, 0, PARABOLIQUE, -1, 500, 500));
	v2.ajouterVaisseau(400, new VaisseauEclaireur(1000, 0, PARABOLIQUE, -1, 500, 500));
	v2.ajouterVaisseau(800, new VaisseauEclaireur(1000, 0, PARABOLIQUE, -1, 500, 500));
	v2.ajouterVaisseau(1200, new VaisseauEclaireur(1000, 0, PARABOLIQUE, -1, 500, 500));
	v2.ajouterVaisseau(1600, new VaisseauEclaireur(1000, 0, PARABOLIQUE, -1, 500, 500));

	v3.ajouterVaisseau(0, new VaisseauEclaireur(1000, 0, SINUS, -1, 300, 100, -.7));
	v3.ajouterVaisseau(500, new VaisseauEclaireur(1000, 0, SINUS, -1, 300, 100, -.7));
	v3.ajouterVaisseau(1000, new VaisseauEclaireur(1000, 0, SINUS, -1, 300, 100, -.7));
	v3.ajouterVaisseau(1500, new VaisseauEclaireur(1000, 0, SINUS, -1, 300, 100, -.7));
	v3.ajouterVaisseau(2000, new VaisseauEclaireur(1000, 0, SINUS, -1, 300, 100, -.7));

	v4.ajouterVaisseau(0, new VaisseauAttaquant(0, -50, PARABOLIQUE, 1, 200, 0));
	v4.ajouterVaisseau(0, new VaisseauAttaquant(250, -50, PARABOLIQUE, 1, 200, 250));
	v4.ajouterVaisseau(0, new VaisseauAttaquant(500, -50, PARABOLIQUE, 1, 200, 500));
	v4.ajouterVaisseau(0, new VaisseauAttaquant(750, -50, PARABOLIQUE, 1, 200, 750));
	v4.ajouterVaisseau(0, new VaisseauAttaquant(1000, -50, PARABOLIQUE, 1, 200, 1000));

	v5.ajouterVaisseau(0, new VaisseauDefenseur(-50, 500, vaisseaux_, LINEAIRE, 1, 0));
	v5.ajouterVaisseau(1500, new VaisseauDefenseur(-50, 500, vaisseaux_, LINEAIRE, 1, 0));
	v5.ajouterVaisseau(3000, new VaisseauDefenseur(-50, 500, vaisseaux_, LINEAIRE, 1, 0));

	pattern_.push_back(v1);
	pattern_.push_back(v2);
	pattern_.push_back(v3);
	pattern_.push_back(v4);
	pattern_.push_back(v5);

	for (auto &vague : pattern_) vague.setEquipeAll(ENNEMI);

}
