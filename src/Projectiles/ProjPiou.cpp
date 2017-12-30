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
	cercleEnglobant_ = sf::CircleShape(sqrt(2*10*10));
	cercleEnglobant_.setOrigin(sqrt(2 * 10 * 10), sqrt(2 * 10 * 10));
	cercleEnglobant_.setPosition(10, 10);
	forme_.emplace_back(new sf::RectangleShape({20,20}));
	
	// Stats
	age_ = 0;
	actif_ = true;

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
	vy_ = -15;

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

void ProjPiou::agit(Entite& proj)
{
	proj.recoitDegats(degats_);
	detruit_ = true;
}
