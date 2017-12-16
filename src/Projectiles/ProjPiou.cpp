#include "ProjPiou.h"



ProjPiou::ProjPiou()
{
}

ProjPiou::ProjPiou(int x, int y)
{
	// Projectile n'intéragit pas avec les autres projectiles
	collisionable_ = false;

	// Gestion du sprite
	texture_.loadFromFile("../../rc/Sprites/base/projectile_test.png");
	sprite_.setTexture(texture_);

	// Hitbox
	cercleEnglobant_ = sf::CircleShape(10);
	cercleEnglobant_.setOrigin(10, 10);
	
	age_ = 0;

	//  Projectile qui se déplace verticalement
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
