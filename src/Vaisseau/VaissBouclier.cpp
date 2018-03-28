#include "VaissBouclier.h"
#include <cmath>


VaissBouclier::VaissBouclier(Ecran& ecran) :
	Vaisseau(ecran)
{	
	// Sprites
	sprites_.emplace_back(ecran_.getChargeur().getTexture("vaiss.bouclier"));
	for (auto& sprite : sprites_)
		sprite.setOrigin({ this->getTaille().x / 2.0f, this->getTaille().y / 2.0f });

	// Cercle englobant / Hitbox simple
	//TODO PG Englobeur
	cercleEnglobant_ = sf::CircleShape(sqrt(10 * 10 + 64 * 64));
	cercleEnglobant_.setOrigin(sqrt(10 * 10 + 64 * 64), sqrt(10 * 10 + 64 * 64));
	cercleEnglobant_.setPosition(64, 10);
	forme_.emplace_back(new sf::RectangleShape({ 128,20 }));

	// Hitbox
	// TODO Hitbox complète

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

void VaissBouclier::gestion(proj_container proj_cont, Input& input)
{
	// Juste pour mute les warnings du compilateur
	(void)input;
	
	if (actif_)
		afficher(debug_);
}