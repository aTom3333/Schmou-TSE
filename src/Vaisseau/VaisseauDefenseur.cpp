#include "VaisseauDefenseur.h"

#include <cmath>


VaisseauDefenseur::VaisseauDefenseur(float x, float y, vaisseau_container &vaisseaux, Trajectoire traj, float param1, float param2, float param3, float param4)
{
	//sprite
	texture_.loadFromFile("../../rc/Sprites/base/vaisseauDefenseur.png");
	sprite_.setTexture(texture_);

	//hitbox simple
	cercleEnglobant_ = sf::CircleShape((float)sqrt(32 * 32 + 64 * 64));
	cercleEnglobant_.setOrigin((float)sqrt(32 * 32 + 64 * 64), sqrt((float)32 * 32 + 64 * 64));
	cercleEnglobant_.setPosition(16, 32);
	forme_.emplace_back(new sf::RectangleShape({ 128,64 }));

	// Initialisation de la position
	posInit_.x = x;
	posInit_.y = y;
	// initialisation de la trajectoire
	trajectoire_ = traj;
	// Initialisation des paramètres de base
	equipe_ = ENNEMI;
	t_ = 0;
	frames_ = 1;
	vit_ = 10;
	actif_ = false;

	pvM_ = 50;
	armureM_ = 50;
	bouclierM_ = 0;

	pv_ = pvM_;
	armure_ = armureM_;
	bouclier_ = bouclierM_;

	regenARM_ = 0;
	regenBOU_ = 0;
	regenPV_ = 0;

	degatsColl_ = 75;

	annexes_.push_back(vaisseau_ptr(new VaisseauDefenseurB(0, x, y+64, this)));
	annexesB_.push_back(true);
	vaisseaux.push_back(annexes_[0]);

	// Initialisation des paramètres de trajectoire
	params_.push_back(param1);
	params_.push_back(param2);
	params_.push_back(param3);
	params_.push_back(param4);

}

VaisseauDefenseur::~VaisseauDefenseur()
{

}

void VaisseauDefenseur::gestion(sf::RenderWindow & window, sf::Time tempsEcoule, Input& input)
{
	/*if (frames_%100==0)
	{
	params_[0] = -params_[0];
	posInit_ = position_;
	t_ = 0;
	frames_ = 0;
	}*/

	if (actif_)
	{
		setPosition(traj_position(trajectoire_, t_, vit_, posInit_, params_));
		afficher(window);

		// Gestion du module de bouclier
		for(unsigned int i = 0; i < annexes_.size(); i++)
		{
			if (annexesB_[i])
			{
				annexes_[i]->setActif(true);
				annexes_[i]->setPosition({ position_.x, position_.y + 64 });
				annexes_[i]->gestion(window, tempsEcoule, input);
			}
		}
			
		t_ += tempsEcoule.asMilliseconds();
		frames_++;
	}
	
}

void VaisseauDefenseur::destruction()
{
	annexesB_[0] = false;
	annexes_[0]->setDetruit(true);
	detruit_ = true;
}