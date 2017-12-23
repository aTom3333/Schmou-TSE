#include "ProjPiou.h"



ProjPiou::ProjPiou()
{
}

ProjPiou::ProjPiou(int x, int y)
{
	// Gestion du sprite
	texture_.loadFromFile("../../rc/Sprites/base/projectile_test.png");
	sprite_.setTexture(texture_);

	// Hitbox
	cercleEnglobant_ = sf::CircleShape(10);
	cercleEnglobant_.setOrigin(5, 5);
	cercleEnglobant_.setPosition(10, 10);
	forme_.emplace_back(new sf::CircleShape(cercleEnglobant_));
	
	age_ = 0;

	//  Projectile qui se déplace verticalement
	vx_ = 0;
	vy_ = -12;

	float x1 = x, y1 = y-20;

	setPosition({ x1,  y1 });
}

ProjPiou::~ProjPiou()
{
}

void ProjPiou::gestion(sf::RenderWindow & window)
{
	setPosition({ position_.x, position_.y + vy_});
	afficher(window);
}

void ProjPiou::agit(Entite& proj)
{
	proj.setDetruit(true);
	detruit_ = true;
}
