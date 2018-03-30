#include "VaissBouclier.h"
#include <cmath>


VaissBouclier::VaissBouclier(Ecran& ecran) :
	Vaisseau(ecran)
{	
	// Sprites
	sprites_.emplace_back(*ecran_.getChargeur().getTexture("vaiss.bouclier"));
	for (auto& sprite : sprites_)
		sprite.setOrigin({ this->getTaille().x / 2.0f, this->getTaille().y / 2.0f });

	// Cercle englobant
	//TODO PG Englobeur
	const float R = hypot(this->getTaille().x / 2.0f, this->getTaille().y / 2.0f);
	cercleEnglobant_ = sf::CircleShape(R);
	cercleEnglobant_.setOrigin(R, R);

	//Hitbox
	forme_.emplace_back(new sf::RectangleShape({ 128,20 }));
	for (auto& forme : forme_)
		forme->setOrigin(forme->getGlobalBounds().width / 2.0f, forme->getGlobalBounds().height / 2.0f);

	//Origine
	origine_ = { this->getTaille().x / 2.0f, this->getTaille().y / 2.0f };

	// Caractéristiques de code
	equipe_ = ENNEMI;
	actif_ = false;
	invincibilable_ = false;

	// Stats
	pv_ = pvM_ = 1;
	armure_ = armureM_ = 0;
	bouclier_ = bouclierM_ = 300;
	vit_ = vitM_ = 0;

	regenARM_ = 0;
	regenBOU_ = 2;
	regenPV_ = 0;

	degatsColl_ = 50;
}

void VaissBouclier::gestion(proj_container& proj_cont, Input& input)
{
	// Juste pour mute les warnings du compilateur
	(void)input;
	
	if (actif_)
		afficher();
}