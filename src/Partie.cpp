#include "Partie.h"
#include "Projectiles/_projectiles.h"
#include "Capacites/_Capacites.h"
#include "Vaisseau/_vaisseaux.h"
#include "Interface/bindings.h"
#include "vague.h"


Partie::Partie(sf::RenderWindow& window) : window_{window}, input_(window, Input::Media::Mouse)
{
	if (!font_.loadFromFile("../../rc/Font/hemi.ttf"))
	{
		std::cout << "Impossible de charger la police" << std::endl;
	}
	
	//set_mouse_default_binding(input_);
	set_keyboard_default_binding_2(input_);
	afficheHUD_ = true;
}

Partie::~Partie()
{
	for (int i = 0; i < vaisseaux_.size(); i++)
		delete vaisseaux_[i];
	for (int i = 0; i < projectiles_.size(); i++)
		delete projectiles_[i];
}

void Partie::testProjTest()
{
	sf::Clock clock;

	Vague v1(0), v2(5000), v3(10000), v4(15000), v5(10000);

	VaisseauTest *vaisseautest = new VaisseauTest;
	/*VaisseauEclaireur *vaiseauEclaireurL = new VaisseauEclaireur(0, 0, LINEAIRE, 1, 0.5);
	VaisseauEclaireur *vaiseauEclaireurP = new VaisseauEclaireur(1000, 0, PARABOLIQUE, -1, 500, 500);
	VaisseauEclaireur *vaiseauEclaireurS = new VaisseauEclaireur(1000, 0, SINUS, -1, 300, 100, -.7);*/

	//Joueur
	vaisseaux_.push_back(vaisseautest);


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

	v4.ajouterVaisseau(0, new VaisseauAttaquant(0, -50, PARABOLIQUE, 1,    200, 0));
	v4.ajouterVaisseau(0, new VaisseauAttaquant(250, -50, PARABOLIQUE, 1,  200, 250));
	v4.ajouterVaisseau(0, new VaisseauAttaquant(500, -50, PARABOLIQUE, 1,  200, 500));
	v4.ajouterVaisseau(0, new VaisseauAttaquant(750, -50, PARABOLIQUE, 1,  200, 750));
	v4.ajouterVaisseau(0, new VaisseauAttaquant(1000, -50, PARABOLIQUE, 1, 200, 1000));

	v5.ajouterVaisseau(0, new VaisseauDefenseur(-50, 500, vaisseaux_, LINEAIRE, 1, 0));
	v5.ajouterVaisseau(1500, new VaisseauDefenseur(-50, 500, vaisseaux_, LINEAIRE, 1, 0));
	v5.ajouterVaisseau(3000, new VaisseauDefenseur(-50, 500, vaisseaux_, LINEAIRE, 1, 0));



	std::vector<Vague> pattern;

	pattern.push_back(v1);
	pattern.push_back(v2);
	pattern.push_back(v3);
	pattern.push_back(v4);
	pattern.push_back(v5);

	// Modifie la vitesse du jeu (debug)
	timeSpeed_ = 1;

	vaisseaux_[0]->setPosition({ 500,700 });

    // Déplacer la souris à la position du vaisseau
    auto pos = vaisseaux_[0]->getPosition();
    pos.x += 32;
    pos.y += 32;
    sf::Mouse::setPosition(window_.mapCoordsToPixel(pos), window_);

	hud_.init(vaisseaux_[0]);

	while (window_.isOpen())
	{
		// Gestion  des evenement qui n'est pas bien implémentée ! ah si thomas est passé par là :o 
		sf::Event event;
		while (window_.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window_.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
				if(timeSpeed_ < 5)
					timeSpeed_ += 0.1;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
				if(timeSpeed_ > 0.1)
					timeSpeed_ -= 0.1;
		}

		auto t_ecoule = clock.restart();

		t_ecoule = t_ecoule * timeSpeed_;
		
		// Efface l'écran
		window_.clear();
		
		// Gestion des vagues
		for (int i = 0; i < pattern.size(); i++)
			pattern[i].gestion(vaisseaux_, t_ecoule);

		//Gestion des vaisseaux
		for (int i = 0; i < vaisseaux_.size(); i++)
		{
			vaisseaux_[i]->regen(t_ecoule);
			vaisseaux_[i]->gestionCapacite(projectiles_, t_ecoule);
			vaisseaux_[i]->gestion(window_, t_ecoule, input_);
		}

		// Gestion des projectiles_
		for (int i = 0; i < projectiles_.size(); i++)
		{
			projectiles_[i]->regen(t_ecoule);
			projectiles_[i]->gestion(window_, t_ecoule);
		}
			

		// Gestion des collisions
		collisionProjectile();
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

void Partie::collisionProjectile()
{
	/*std::vector<Entite*> allEntite;
	allEntite.insert(projectiles_.begin(), vaisseaux_.begin(), vaisseaux_.end());*/
	int n = projectiles_.size() + vaisseaux_.size();
	Entite **allEntite = new Entite*[projectiles_.size() + vaisseaux_.size()];

	for (int i = 0; i < projectiles_.size(); i++)
		allEntite[i] = projectiles_[i];
	for (int i = projectiles_.size(); i < n; i++)
		allEntite[i] = vaisseaux_[i - projectiles_.size()];


	if (projectiles_.size() != 0)
	{
		for (int i = 0; i < projectiles_.size() - 1; i++)
		{
			// Si le projectile est dehors
			if (projectiles_[i]->estDehors())
				projectiles_[i]->destruction();
			else
			{
				// Collision avec une autre entite
				for (int j = i + 1; j < projectiles_.size() + vaisseaux_.size(); j++)
				{
					if (collision(*allEntite[i], *allEntite[j]))
						allEntite[i]->agit(*allEntite[j]);
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
		for (int i = 0; i < vaisseaux_.size() - 1; i++)
		{
			// Si le vaisseau est dehors
			if (vaisseaux_[i]->estDehors())
				vaisseaux_[i]->destruction();
			else
			{
				for (int j = i + 1; j < vaisseaux_.size(); j++)
				{
					if (collision(*vaisseaux_[i], *vaisseaux_[j]))
						vaisseaux_[j]->agit(*vaisseaux_[i]);
				}
			}
			
		}
	}
	deleteVaisseauDetruit();
}

void Partie::deleteProjectileDetruit()
{
	for (int i = 0; i < projectiles_.size(); i++)
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
	for (int i = 0; i < vaisseaux_.size(); i++)
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
