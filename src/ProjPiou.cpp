#include "ProjPiou.h"

ProjPiou::ProjPiou()
{
}

ProjPiou::ProjPiou(int x, int y)
{
	collisionable_ = false;
	texture_.loadFromFile("../../rc/Sprites/base/projectile_test.png");
	cercleEnglobant_ = sf::CircleShape(10);
	cercleEnglobant_.setOrigin(10, 10);
	sprite_.setTexture(texture_);
	age_ = 0;
	vx_ = 0;
	vy_ = -8;

	float x1 = x, y1 = y;

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
