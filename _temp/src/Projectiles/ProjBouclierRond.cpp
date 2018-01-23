#include "ProjBouclierRond.h"

ProjBouclierRond::ProjBouclierRond(){}


ProjBouclierRond::ProjBouclierRond(Entite* Entite_liee, int pvM, int degatsColl)
{
	// Sprite
	texture_.loadFromFile("../../rc/Sprites/base/bouclier_rond.png");
	sprite_.setTexture(texture_);

	// Hitbox
	cercleEnglobant_ = sf::CircleShape(sqrt(2 * 35 * 35));
	cercleEnglobant_.setOrigin(10, 10);
	cercleEnglobant_.setPosition(10, 10);
	forme_.emplace_back(new sf::CircleShape(sqrt(2 * 35 * 35)));

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

	degatsColl_ = degatsColl; 

	//Entité à laquelle est rattaché le bouclier
	Entite_liee_ = Entite_liee;

}

void ProjBouclierRond::gestion(sf::RenderWindow & window, sf::Time tempsEcoule)
{
	setPosition({ Entite_liee_->getPosition().x, Entite_liee_->getPosition().y});
	afficher(window);
}


void ProjBouclierRond::agit(Entite& proj)
{
	proj.recoitDegats(degatsColl_);
	detruit_ = true;
}