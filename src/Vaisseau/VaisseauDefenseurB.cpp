#include "VaisseauDefenseurB.h"
#include <cmath>


VaisseauDefenseurB::VaisseauDefenseurB(int nb, float x, float y, Vaisseau *createur)
{
	// Juste pour mute les warnings du compilateur
	(void)x;
	(void)y;
	
	//sprite
	texture_.loadFromFile("../../rc/Sprites/base/vaisseauDefenseurBouclier.png");
	sprite_.setTexture(texture_);

	//hitbox simple
	cercleEnglobant_ = sf::CircleShape(sqrt(10 * 10 + 64 * 64));
	cercleEnglobant_.setOrigin(sqrt(10 * 10 + 64 * 64), sqrt(10 * 10 + 64 * 64));
	cercleEnglobant_.setPosition(64, 10);
	forme_.emplace_back(new sf::RectangleShape({ 128,20 }));

	equipe_ = ENNEMI;
	vit_ = 0;
	actif_ = false;
	nbModule_ = nb;

	pvMax_ = 1;
	armureMax_ = 0;
	bouclierMax_ = 300;

	pv_ = pvMax_;
	armure_ = armureMax_;
	bouclier_ = bouclierMax_;

	regenARM_ = 0;
	regenBOU_ = 2;
	regenPV_ = 0;

	degats_ = 0;

	createur_ = createur;
}

VaisseauDefenseurB::~VaisseauDefenseurB()
{
}

void VaisseauDefenseurB::gestion(sf::RenderWindow & window, sf::Time tempsEcoule, Input& input)
{
	// Juste pour mute les warnings du compilateur
	(void)tempsEcoule;
	(void)input;
	
	if (actif_)
		afficher(window);
}
void VaisseauDefenseurB::destruction()
{
	createur_->setAnnexeB(nbModule_, false);
	detruit_ = true;
}
