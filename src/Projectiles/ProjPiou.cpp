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
	
	// Stats
	age_ = 0;

	pvMax_ = 10;
	armureMax_ = 0;
	bouclierMax_ = 0;

	pv_ = pvMax_;
	armure_ = armureMax_;
	bouclier_ = bouclierMax_;

	regenARM_ = regenBOU_ = regenPV_ = 0;

	degats_ = 70;

	//  Projectile qui se déplace verticalement
	vx_ = 0;
	vy_ = -20;

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
	proj.recoitDegats(degats_);
	detruit_ = true;
}
