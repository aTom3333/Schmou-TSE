#include "ProjTest.h"


ProjTest::ProjTest()
{

	//sprite
	texture_.loadFromFile("../../rc/Sprites/base/balle.png");
	sprite_.setTexture(texture_);

	//hitbox simple (et complète dans ce cas car c'est le projectile est un cercle)
	cercleEnglobant_ =  sf::CircleShape(16);
	cercleEnglobant_.setOrigin(16, 16);

	//attributs
	age_ = 0;

	
	mx_ = rand() % 2 == 0 ? 1 : -1;
	my_ = rand() % 2 == 0 ? 1 : -1;
	vx_ = rand() % 5 + 3;
	vy_ = rand() % 5 + 3;
	

	float x = rand() % 800, y = rand() % 600;

	setPosition({ x,  y});
}

ProjTest::~ProjTest()
{
}

void ProjTest::gestion(sf::RenderWindow& window)
{
	age_++;

	setPosition({ position_.x + vx_*mx_, position_.y + vy_*my_ });

	if (position_.x > 800) mx_ = -1;
	if (position_.x < 0) mx_ = 1;
	if (position_.y > 600) my_ = -1;
	if (position_.y < 0) my_ = 1;

	afficher(window);
}

