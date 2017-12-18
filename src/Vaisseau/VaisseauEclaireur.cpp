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
	x0_ = x;
	y0_ = y;
	// initialisation de la trajectoire
	trajectoire_ = traj;
	// Initialisation des paramètres de base
	t_ = 0;
	vit_ = 40;

	// Initialisation des paramètres de trajectoire
	param1_ = param1;
	param2_ = param2;
	param3_ = param3;
	param4_ = param4;

}

VaisseauEclaireur::~VaisseauEclaireur()
{
}

void VaisseauEclaireur::gestion(sf::RenderWindow & window, float tempsEcoule)
{
	// Nouvelles coordonnées
	float x = 0, y = 0;

	switch (trajectoire_)
	{
		// Si la trajectoire est linéaire
		case LINEAIRE:
			x = x0_ + param2_*vit_*t_/100;
			y = param1_ * (x - x0_) + y0_;
			break;
		// Si la trajectoire est parabolique
		case PARABOLIQUE:
			x = x0_ + param3_*vit_*t_/100;
			y = (y0_ - param2_) / ((x0_ - param1_)*(x0_ - param1_)) * (x - param1_) * (x - param1_) + param2_;
			break;
		// Si la trajectoire est sinusoidale
		case SINUS:
			x = x0_ + param4_*vit_*t_/130;
			y = param1_ * (x-x0_) + y0_ + param3_ * sin(2 * PI / param2_ * x);
			break;
		default:
			break;
	}

	setPosition(sf::Vector2f(x, y));
	afficher(window);

	t_ += tempsEcoule;
}
