#include "ProjPiou.h"
#include <cmath>


ProjPiou::ProjPiou()
{
}

ProjPiou::ProjPiou(int x, int y, Equipe equipe)
{
	// Gestion du sprite
	//texture_.loadFromFile("../../rc/Sprites/base/projectile_test.png");
	texture_.loadFromFile("../../rc/Sprites/Capacites/Piou20x30.PNG");
	sprite_.setTexture(texture_);

	// Hitbox
	cercleEnglobant_ = sf::CircleShape(5);
	cercleEnglobant_.setOrigin(10, 10);
	cercleEnglobant_.setPosition(10, 10);
	forme_.emplace_back(new sf::RectangleShape({20,30}));
	
	// Stats
	equipe_ = equipe;
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
	vit_ = 700;

	float x1 = x, y1 = y;

	setPosition({ x1,  y1 });
}

ProjPiou::~ProjPiou()
{
}

void ProjPiou::gestion(sf::RenderWindow & window, sf::Time tempsEcoule)
{
	setPosition({ position_.x, position_.y - vit_ * tempsEcoule.asSeconds()});
	afficher(window);
}

void ProjPiou::agit(Entite& proj)
{
	proj.recoitDegats(degats_);
	detruit_ = true;
}
