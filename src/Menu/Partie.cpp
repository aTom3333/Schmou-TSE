#include "Partie.h"
#include "../Projectiles/_projectiles.h"
#include "../Capacites/_Capacites.h"
#include "../Vaisseau/_vaisseaux.h"
#include "../Interface/bindings.h"
#include "../Pattern/Vague.h"
#include "Ecran.h"
#include "Hangar.h"
#include "../Utilitaires/Divers.h"


Partie::Partie(sf::RenderWindow& window, Input::Media media, bool afficheHUD, bool avecPattern) : input_{window, media}, avecPattern_{avecPattern}, afficheHUD_{afficheHUD}, Ecran(window)
{
	if (!font_.loadFromFile("../../rc/Font/hemi.ttf"))
	{
		std::cout << "Impossible de charger la police" << std::endl;
	}
	
	if (media == Input::Media::Mouse)set_mouse_default_binding(input_);
	if (media == Input::Media::Keyboard)set_keyboard_default_binding(input_);
	if (media == Input::Media::Joypad)set_joypad_default_binding(input_);

	//Joueur
	vaisseau_container::value_type vaisseautest(new VaisseauTest(*this));
	vaisseautest->setEquipe(JOUEUR);
	
	// Capacités
	//TIR1 Piou
	vaisseautest->addCapacite(new CapPiou(*this, vaisseautest));
	//TIR2 Dash
	vaisseautest->addCapacite(new CapDash(*this, vaisseautest));
	//COMP1 BouclierRond
	vaisseautest->addCapacite(new CapBouclierRond(*this, vaisseautest));
	//COMP2 Missile
	vaisseautest->addCapacite(new CapMissile(*this, vaisseautest));
	vaisseautest->getCapacites().at(3)->setAutoAim(true);
	//COMP3 Boing
	vaisseautest->addCapacite(new CapBoing(*this, vaisseautest));
	//ULTI Bismillah
	vaisseautest->addCapacite(new CapBismillah(*this, vaisseautest));
	
	vaisseaux_.push_back(vaisseautest);
	vaisseaux_[0]->setPosition({ 500,700 });


	//Fond défilant
	fondTexture_.emplace_back(new sf::Texture());
	fondTexture_.back()->loadFromFile("../../rc/Fond/etoiles1.png");
	fond_.emplace_back(sf::Sprite(*fondTexture_.back()));
	offset_.push_back(0);

	fondTexture_.emplace_back(new sf::Texture());
	fondTexture_.back()->loadFromFile("../../rc/Fond/etoiles2.png");
	fond_.emplace_back(sf::Sprite(*fondTexture_.back()));
	offset_.push_back(0);

	

	//init patterns
	if (avecPattern_) initPatternTest();

	// Modifie la vitesse du jeu (debug)
	coeffTemps_ = 1;

	//Initialise le HUD
	hud_.init(vaisseaux_[0]);

}

Partie::~Partie()
{}

ecran_t Partie::executer(std::vector<std::unique_ptr<Ecran>>& vectEtats, sf::Texture &derniereFenetre)
{
	//horloge
	horloge_.restart();

	// Temps
	sf::Time t_previous = sf::Time::Zero;
	std::pair<sf::Time, size_t> countFPS;
	float fps = 0;

    // Déplacer la souris à la position du vaisseau
    auto pos = vaisseaux_[0]->getPosition();
    pos.x += 32;
    pos.y += 32;
    sf::Mouse::setPosition(window_.mapCoordsToPixel(pos), window_);


	while (window_.isOpen())
	{
		// Gestion  des événements 
		sf::Event event;
		while (window_.pollEvent(event))
		{
			auto retour = gestionEvent(event);
			if(retour) {
			    derniereFenetre.update(window_);
			    if(retour == HANGAR)
			        vectEtats[HANGAR]->setVaisseau(vaisseaux_.front());
			    return *retour;
			}
		}
            
		//gestion du temps
		t_frame_ = (horloge_.getElapsedTime() - t_previous) * coeffTemps_;
		t_previous = horloge_.getElapsedTime();

		// Efface l'écran
		window_.clear();

		//Fond défilant
		gestionFond(t_frame_);

		// Gestion des vagues
		if (avecPattern_)
		{
			for(unsigned int i = 0; i < pattern_.size(); i++)
				pattern_[i].gestion(vaisseaux_);
		}

		//Gestion des vaisseaux
		for(auto& vaisseau : vaisseaux_)
		{
			vaisseau->regen();
			vaisseau->gestion(projectiles_, input_);
			vaisseau->gestionCapacite(projectiles_);
		}

		// Gestion des projectiles_
		for(auto& proj : projectiles_)
		{
			proj->regen();
			proj->gestion();
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

		//calcul FPS
		countFPS.first += t_frame_;
		countFPS.second++;
		if (countFPS.second == 10)
		{
			fps = 10 * coeffTemps_ / countFPS.first.asSeconds();
			countFPS.second = 0;
			countFPS.first = sf::Time::Zero;
		}

		window_.setTitle("Schmou'TSE - Vitesse de jeu : " + std::to_string(coeffTemps_) + " FPS : " + std::to_string(fps));
		sf::sleep(sf::milliseconds(10));

	}

	return VIDE;
}

std::unique_ptr<Ecran> Partie::factory()
{
	return std::unique_ptr<Ecran>(new Partie(window_, input_.get_media(), afficheHUD_, avecPattern_));
}

void Partie::collisionProjectile()
{
	/*std::vector<Entite*> allEntite;
	allEntite.insert(projectiles_.begin(), vaisseaux_.begin(), vaisseaux_.end());*/
	size_t n = projectiles_.size() + vaisseaux_.size();
	std::vector<std::shared_ptr<Entite> > allEntite(n);

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
						if (allEntite[i]->isCollisionneuse() && allEntite[j]->isCollisionnable()) allEntite[i]->agit(*allEntite[j]);
						if (allEntite[j]->isCollisionneuse() && allEntite[i]->isCollisionnable()) allEntite[j]->agit(*allEntite[i]);
					}
						
				}
			}		
		}
	}
	deleteProjectileDetruit();
	deleteVaisseauDetruit();
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
	for(auto it = projectiles_.begin(); it != projectiles_.end();)
	{
		if ((*it)->estDetruit())//teste si détruit ou si pv <=0;
		{
			it = projectiles_.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void Partie::deleteVaisseauDetruit()
{
	for(auto it = vaisseaux_.begin(); it != vaisseaux_.end();)
	{
		if ((*it)->estDetruit())//teste si détruit ou si pv <=0;
		{
			it = vaisseaux_.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void Partie::gestionFond(sf::Time t)
{
	float coeff_vitesse_fond = 5;

	for (size_t i = 0; i < fond_.size(); i++)
	{
		offset_[i] += (i+1) * 100 * t.asSeconds() * coeff_vitesse_fond;
		if (offset_[i] > fond_[i].getGlobalBounds().height) offset_[i] = 0;

		fond_[i].setPosition(0, offset_[i]);
		window_.draw(fond_[i]);

		fond_[i].setPosition(0, offset_[i] - fond_[i].getGlobalBounds().height);
		window_.draw(fond_[i]);
	}
	
}

void Partie::initPatternTest()
{
	std::cerr << sizeof(long long int) << std::endl << sizeof(long int) << std::endl << sizeof(int) << std::endl << sizeof(short int) << std::endl << sizeof(unsigned int) << std::endl << std::endl << std::endl << sizeof(long double) << std::endl << sizeof(double) << std::endl << sizeof(float) << std::endl << std::endl << sizeof(signed char) << std::endl << sizeof(unsigned char) << std::endl << sizeof(bool) << std::endl;

	Vague v1(*this, sf::seconds(0)),
		  v2(*this, sf::seconds(5)),
		  v3(*this, sf::seconds(10)),
		  v4(*this, sf::seconds(15)),
		  v5(*this, sf::seconds(10));

	/*VaisseauEclaireur *vaiseauEclaireurL = new VaisseauEclaireur(0, 0, LINEAIRE, 1, 0.5);
	VaisseauEclaireur *vaiseauEclaireurP = new VaisseauEclaireur(1000, 0, PARABOLIQUE, -1, 500, 500);
	VaisseauEclaireur *vaiseauEclaireurS = new VaisseauEclaireur(1000, 0, SINUS, -1, 300, 100, -.7);*/

	//TODO tests à enlever
	v1.ajouterElement({ sf::milliseconds(0), vaisseau_ptr(new VaisseauAttaquant(*this,ECRAN_L/2, ECRAN_H/2, LINEAIRE, 0, 0)) });
	v1.getElements().at(0).vaiss->addCapacite(new CapMissile(*this, v1.getElements().at(0).vaiss));
	v1.getElements().at(0).vaiss->getCapacites().at(0)->setAutoAim(true);
	v1.getElements().at(0).vaiss->setPvMax(std::numeric_limits<float>::max());
	v1.ajouterElement({ sf::milliseconds(0), vaisseau_ptr(new VaisseauDefenseur(*this, -50, 500, vaisseaux_, LINEAIRE, 1, 0)) });
	v1.getElements().at(1).vaiss->setPv(1);
	v1.getElements().at(1).vaiss->getAnnexes().at(0)->setPv(2);
	

	v1.ajouterElement({ sf::milliseconds(0), vaisseau_ptr(new VaisseauEclaireur(*this, 0, 0, LINEAIRE, 1, 0.5)) });
	v1.ajouterElement({ sf::milliseconds(400), vaisseau_ptr(new VaisseauEclaireur(*this, 0, 0, LINEAIRE, 1, 0.5)) });
	v1.ajouterElement({ sf::milliseconds(800), vaisseau_ptr(new VaisseauEclaireur(*this, 0, 0, LINEAIRE, 1, 0.5)) });
	v1.ajouterElement({ sf::milliseconds(1200), vaisseau_ptr(new VaisseauEclaireur(*this, 0, 0, LINEAIRE, 1, 0.5)) });
	v1.ajouterElement({ sf::milliseconds(1600), vaisseau_ptr(new VaisseauEclaireur(*this, 0, 0, LINEAIRE, 1, 0.5)) });

	v2.ajouterElement({ sf::milliseconds(0), vaisseau_ptr(new VaisseauEclaireur(*this, 1000, 0, PARABOLIQUE, -1, 500, 500)) });
	v2.ajouterElement({ sf::milliseconds(400), vaisseau_ptr(new VaisseauEclaireur(*this, 1000, 0, PARABOLIQUE, -1, 500, 500)) });
	v2.ajouterElement({ sf::milliseconds(800), vaisseau_ptr(new VaisseauEclaireur(*this, 1000, 0, PARABOLIQUE, -1, 500, 500)) });
	v2.ajouterElement({ sf::milliseconds(1200), vaisseau_ptr(new VaisseauEclaireur(*this, 1000, 0, PARABOLIQUE, -1, 500, 500)) });
	v2.ajouterElement({ sf::milliseconds(1600), vaisseau_ptr(new VaisseauEclaireur(*this, 1000, 0, PARABOLIQUE, -1, 500, 500)) });

	v3.ajouterElement({ sf::milliseconds(0), vaisseau_ptr(new VaisseauEclaireur(*this, 1000, 0, SINUS, -1, 300, 100, -.7)) });
	v3.ajouterElement({ sf::milliseconds(500), vaisseau_ptr(new VaisseauEclaireur(*this, 1000,0, SINUS, -1, 300, 100, -.7)) });
	v3.ajouterElement({ sf::milliseconds(1000), vaisseau_ptr(new VaisseauEclaireur(*this, 1000, 0, SINUS, -1, 300, 100, -.7)) });
	v3.ajouterElement({ sf::milliseconds(1500), vaisseau_ptr(new VaisseauEclaireur(*this, 1000, 0, SINUS, -1, 300, 100, -.7)) });
	v3.ajouterElement({ sf::milliseconds(2000), vaisseau_ptr(new VaisseauEclaireur(*this, 1000, 0, SINUS, -1, 300, 100, -.7)) });

	v4.ajouterElement({ sf::milliseconds(0), vaisseau_ptr(new VaisseauAttaquant(*this, 0, -50, PARABOLIQUE, 1, 200, 0)) });
	v4.ajouterElement({ sf::milliseconds(0), vaisseau_ptr(new VaisseauAttaquant(*this, 250, -50, PARABOLIQUE, 1, 200, 250)) });
	v4.ajouterElement({ sf::milliseconds(0), vaisseau_ptr(new VaisseauAttaquant(*this, 500, -50, PARABOLIQUE, 1, 200, 500)) });
	v4.ajouterElement({ sf::milliseconds(0), vaisseau_ptr(new VaisseauAttaquant(*this, 750, -50, PARABOLIQUE, 1, 200, 750)) });
	v4.ajouterElement({ sf::milliseconds(0), vaisseau_ptr(new VaisseauAttaquant(*this, 1000, -50, PARABOLIQUE, 1, 200, 1000)) });
	for(auto& vaisseau : v4)
		vaisseau.vaiss->addCapacite(new CapMissile(*this, vaisseau.vaiss));

	v5.ajouterElement({ sf::milliseconds(0), vaisseau_ptr(new VaisseauDefenseur(*this, -50, 500, vaisseaux_, LINEAIRE, 1, 0)) });
	v5.ajouterElement({ sf::milliseconds(1500), vaisseau_ptr(new VaisseauDefenseur(*this, -50, 500, vaisseaux_, LINEAIRE, 1, 0)) });
	v5.ajouterElement({ sf::milliseconds(3000), vaisseau_ptr(new VaisseauDefenseur(*this, -50, 500, vaisseaux_, LINEAIRE, 1, 0)) });

	pattern_.push_back(v1);
	pattern_.push_back(v2);
	pattern_.push_back(v3);
	pattern_.push_back(v4);
	pattern_.push_back(v5);

	for (auto &vague : pattern_) vague.setEquipeAll(ENNEMI);
}

std::optional<ecran_t> Partie::gestionEvent(const sf::Event& event)
{
    auto retour = Ecran::gestionEvent(event);
    if(retour)
        return retour;
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        detruit_ = true;
        return std::make_optional(ACCUEIL);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
    {
        if (coeffTemps_ < 20)
            coeffTemps_ += 0.1f;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
    {
        if (coeffTemps_ >= 0.1)
            coeffTemps_ -= 0.1f;
        else if (coeffTemps_ > 0.01)
            coeffTemps_ -= 0.01f;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
    {
        return std::make_optional(HANGAR);
    }
	
	return std::nullopt;
}
