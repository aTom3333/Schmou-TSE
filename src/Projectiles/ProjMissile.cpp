#include "ProjMissile.h"

ProjMissile::ProjMissile()
{

}

ProjMissile::ProjMissile(float x, float y)
{
	// Gestion du sprite
	texture_.loadFromFile("../../rc/Sprites/base/projectile_missile.png");
	sprite_.setTexture(texture_);

	// Hitbox
	cercleEnglobant_ = sf::CircleShape(40);
	cercleEnglobant_.setOrigin(20, 40);
	cercleEnglobant_.setPosition(20, 40);
	//forme_.emplace_back(new sf::RectangleShape({40,80}));

	//stats
	pvMax_ = 10;
	armureMax_ = 0;
	bouclierMax_ = 0;

	pv_ = pvMax_;
	armure_ = armureMax_;
	bouclier_ = bouclierMax_;

	regenARM_ = regenBOU_ = regenPV_ = 0;

	degats_ = 200;

	//  Projectile qui se d�place verticalement
	sens_ = 1;
	a_ = 1.05 * sens_;
	v_ = 0.1 * sens_;
	setPosition({ x, y });
}

ProjMissile::~ProjMissile()
{
}

void ProjMissile::gestion(sf::RenderWindow & window)
{
	v_ *= a_;
	if (v_ > 30)
		v_ = 30;
	setPosition({ position_.x, position_.y + v_ });
	afficher(window);
}

void ProjMissile::agit(Entite & e)
{
	e.recoitDegats(degats_);
	detruit_ = true;
}
