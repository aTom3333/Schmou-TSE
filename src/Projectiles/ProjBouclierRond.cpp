#include "ProjBouclierRond.h"
#include <cmath>


ProjBouclierRond::ProjBouclierRond(){}


ProjBouclierRond::ProjBouclierRond(Entite* Entite_liee, int pvM, int degatsColl, float tempsMax, Equipe equipe)
{
	// Sprite
	texture_.loadFromFile("../../rc/Sprites/base/bouclier_rond.png");
	sprite_.setTexture(texture_);

	// Hitbox
	cercleEnglobant_ = sf::CircleShape(75);
	cercleEnglobant_.setOrigin(75, 75);
	cercleEnglobant_.setPosition(75, 75);
	forme_.emplace_back(new sf::CircleShape(cercleEnglobant_));

	// Stats
	age_ = 0;
	actif_ = true;

	pvMax_ = pvM;
	armureMax_ = 0;
	bouclierMax_ = 0;

	pv_ = pvMax_;
	armure_ = 0;
	bouclier_ = 0;

	regenARM_ = regenBOU_ = regenPV_ = 0;

	degats_ = degatsColl; 

	//Entité à laquelle est rattaché le bouclier
	Entite_liee_ = Entite_liee;
	equipe_ = JOUEUR;

	tempsMax_ = tempsMax;
	t_ = 0;

}

void ProjBouclierRond::gestion(sf::RenderWindow & window, sf::Time tempsEcoule)
{
	setPosition({ Entite_liee_->getPosition().x - 75 + 35, Entite_liee_->getPosition().y - 75 + 35});
	afficher(window);
	t_ += tempsEcoule.asMilliseconds();
	if (t_ > tempsMax_)
		detruit_ = true;
}


void ProjBouclierRond::agit(Entite& proj)
{
	proj.recoitDegats(degats_);
	pv_ -= proj.getDegats();
	int alpha = (int)(pv_ / pvMax_ * 255);
	sprite_.setColor({ 255, 255, 255, ( sf::Uint8)alpha });
	if (pv_ < 0)
		detruit_ = true;
}