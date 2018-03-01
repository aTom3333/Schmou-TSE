#include "VaisseauAttaquant.h"
#include <cmath>


VaisseauAttaquant::VaisseauAttaquant(float x, float y, Trajectoire traj, float param1, float param2, float param3, float param4)
{
	//sprite
	texture_.loadFromFile("../../rc/Sprites/base/vaisseauAttaquant.png");
	sprite_.setTexture(texture_);

	//hitbox simple
	cercleEnglobant_ = sf::CircleShape(sqrt(32 * 32 + 64 * 64));
	cercleEnglobant_.setOrigin(sqrt(32 * 32 + 64 * 64), sqrt(32 * 32 + 64 * 64));
	cercleEnglobant_.setPosition(64, 32);
	forme_.emplace_back(new sf::CircleShape(cercleEnglobant_));

	// Initialisation de la postion
	posInit_.x = x;
	posInit_.y = y;
	// initialisation de la trajectoire
	trajectoire_ = traj;
	// Initialisation des paramètres de base
	t_ = 0;
	frames_ = 1;
	vit_ = 40;
	actif_ = false;

	pvMax_ = 300;
	armureMax_ = 50;
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

	capacites_.push_back(new CapMissile());
}

VaisseauAttaquant::~VaisseauAttaquant()
{
}

void VaisseauAttaquant::gestion(sf::RenderWindow & window, sf::Time tempsEcoule, Input& input)
{
	if (actif_)
	{
		if (t_ > 1000)
			capacites_[0]->utiliser(position_.x + 32 + 20, position_.y + 2*sqrt(32 * 32 + 64 * 64));

		setPosition(traj_position(trajectoire_, t_, vit_, posInit_, params_));
		afficher(window);

		t_ += tempsEcoule.asMilliseconds();
		frames_++;
	}
}

