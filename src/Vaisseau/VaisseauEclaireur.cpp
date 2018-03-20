#include "VaisseauEclaireur.h"
#include <cmath>


VaisseauEclaireur::VaisseauEclaireur(double x, double y,Trajectoire traj, double param1, double param2, double param3, double param4)
{
	//sprite
	texture_.loadFromFile("../../rc/Sprites/base/vaisseauEnnemiTest.png");
	sprite_.setTexture(texture_);

	//hitbox simple
	cercleEnglobant_ = sf::CircleShape((float)sqrt(2*32*32));
	cercleEnglobant_.setOrigin((float)sqrt(2 * 32 * 32), (float)sqrt(2 * 32 * 32));
	cercleEnglobant_.setPosition(16, 32);
	forme_.emplace_back(new sf::CircleShape(cercleEnglobant_));

	// Initialisation de la position
	posInit_.x = (float)x;
	posInit_.y = (float)y;
	// initialisation de la trajectoire
	trajectoire_ = traj;
	// Initialisation des paramètres de base
	equipe_ = ENNEMI;
	t_ = 0;
	frames_ = 1;
	vit_ = 30;
	actif_ = false;

	pvM_ = 50;
	armureM_ = 0;
	bouclierM_ = 0;

	pv_ = pvM_;
	armure_ = armureM_;
	bouclier_ = bouclierM_;

	regenARM_ = 0;
	regenBOU_ = 0;
	regenPV_ = 0;

	degatsColl_ = 50;

	// Initialisation des paramètres de trajectoire
	params_.push_back((float)param1);
	params_.push_back((float)param2);
	params_.push_back((float)param3);
	params_.push_back((float)param4);

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

