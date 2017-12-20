#include "VaisseauEclaireur.h"
#include <cmath>


VaisseauEclaireur::VaisseauEclaireur(float x, float y,Trajectoire traj, float param1, float param2, float param3, float param4)
{
	//sprite
	texture_.loadFromFile("../../rc/Sprites/base/vaisseauEnnemiTest.png");
	sprite_.setTexture(texture_);

	//hitbox simple
	cercleEnglobant_ = sf::CircleShape(32);
	cercleEnglobant_.setOrigin(16, 32);

	// Initialisation de la postion
	posInit_.x = x;
	posInit_.y = y;
	// initialisation de la trajectoire
	trajectoire_ = traj;
	// Initialisation des paramètres de base
	t_ = 0;
	frames_ = 1;
	vit_ = 40;

	// Initialisation des paramètres de trajectoire
	params_.push_back(param1);
	params_.push_back(param2);
	params_.push_back(param3);
	params_.push_back(param4);

}

VaisseauEclaireur::~VaisseauEclaireur()
{
}

void VaisseauEclaireur::gestion(sf::RenderWindow & window, float tempsEcoule)
{
	if (frames_%100==0)
	{
		params_[0] = -params_[0];
		posInit_ = position_;
		t_ = 0;
		frames_ = 0;
	}
	


	setPosition(traj_position(trajectoire_,t_,vit_,posInit_,params_));
	afficher(window);

	t_ += tempsEcoule;
	frames_++;
}
