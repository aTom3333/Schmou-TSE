#include "VaisseauEclaireur.h"
#include <cmath>


VaisseauEclaireur::VaisseauEclaireur(float x, float y,Trajectoire traj, float param1, float param2, float param3, float param4)
{
	//sprite
	texture_.loadFromFile("../../rc/Sprites/base/vaisseauEnnemiTest.png");
	sprite_.setTexture(texture_);

	//hitbox simple
	cercleEnglobant_ = sf::CircleShape(sqrt(2*32*32));
	cercleEnglobant_.setOrigin(sqrt(2 * 32 * 32), sqrt(2 * 32 * 32));
	cercleEnglobant_.setPosition(16, 32);
	forme_.emplace_back(new sf::CircleShape(cercleEnglobant_));

	// Initialisation de la postion
	posInit_.x = x;
	posInit_.y = y;
	// initialisation de la trajectoire
	trajectoire_ = traj;
	// Initialisation des paramètres de base
	equipe_ = ENNEMI;
	t_ = 0;
	frames_ = 1;
	vit_ = 30;
	actif_ = false;

	pvMax_ = 50;
	armureMax_ = 0;
	bouclierMax_ = 0;

	pv_ = pvMax_;
	armure_ = armureMax_;
	bouclier_ = bouclierMax_;

	regenARM_ = 0;
	regenBOU_ = 0;
	regenPV_ = 0;

	degats_ = 50;

	// Initialisation des paramètres de trajectoire
	params_.push_back(param1);
	params_.push_back(param2);
	params_.push_back(param3);
	params_.push_back(param4);

}

VaisseauEclaireur::~VaisseauEclaireur()
{
}

void VaisseauEclaireur::gestion(sf::RenderWindow & window, sf::Time tempsEcoule, Input& input)
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

		t_ += tempsEcoule.asMilliseconds();
		frames_++;
	}
}

