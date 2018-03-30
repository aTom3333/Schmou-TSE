#include "VaisseauAttaquant.h"
#include <cmath>


VaisseauAttaquant::VaisseauAttaquant(Ecran& ecran, float x, float y, Trajectoire traj, float param1, float param2, float param3, float param4) : 
	Vaisseau(ecran)
{
	// Sprites
	sprites_.emplace_back(*ecran_.getChargeur().getTexture("vaiss.attaquant"));
	for (auto& sprite : sprites_)
		sprite.setOrigin({ this->getTaille().x / 2.0f, this->getTaille().y / 2.0f });

	// Cercle englobant / Hitbox simple
	//TODO PG Englobeur
	cercleEnglobant_ = sf::CircleShape(sqrt(32 * 32 + 64 * 64));
	cercleEnglobant_.setOrigin(sqrt(32 * 32 + 64 * 64), sqrt(32 * 32 + 64 * 64));
	cercleEnglobant_.setPosition(64, 32);
	forme_.emplace_back(new sf::CircleShape(cercleEnglobant_));

	// Hitbox
	// TODO Hitbox complète

	//Origine
	origine_ = { this->getTaille().x / 2.0f, this->getTaille().y / 2.0f };

	// Caractéristiques de code
	equipe_ = ENNEMI;
	actif_ = false;

	// Stats
	pv_ = pvM_ = 300;
	armure_ = armureM_ = 0;
	bouclier_ = bouclierM_ = 0;
	vit_ = vitM_ = 300;

	regenARM_ = 0;
	regenBOU_ = 0;
	regenPV_ = 0;

	degatsColl_ = 50;

	// Initialisation de la trajectoire
	trajectoire_ = traj;
	params_.push_back(param1);
	params_.push_back(param2);
	params_.push_back(param3);
	params_.push_back(param4);

	// Position initiale
	setPosition({ x, y });
	posInit_ = getPosition();
}

void VaisseauAttaquant::gestion(proj_container &proj_cont, Input& input)
{
	// Juste pour mute les warnings du compilateur
	(void)input;
	
	if (actif_)
	{
		if (t_age_.asMilliseconds() > 1000)
			capacites_[0]->utiliser(proj_cont);

		setPosition(traj_position(trajectoire_,t_age_, vit_, posInit_, params_));
		afficher();

		t_age_ += ecran_.getTempsFrame();
	}
}

