#include "VaisseauEclaireur.h"
#include <cmath>


VaisseauEclaireur::VaisseauEclaireur(double x, double y,Trajectoire traj, double param1, double param2, double param3, double param4)
{
	// Sprites
	sprites_.emplace_back(ecran_.getChargeur().getTexture("vaiss.ennemi.test"));
	for (auto& sprite : sprites_)
		sprite.setOrigin({ this->getTaille().x / 2.0f, this->getTaille().y / 2.0f });

	// Cercle englobant / Hitbox simple
	//TODO PG Englobeur
	cercleEnglobant_ = sf::CircleShape((float)sqrt(2*32*32));
	cercleEnglobant_.setOrigin((float)sqrt(2 * 32 * 32), (float)sqrt(2 * 32 * 32));
	cercleEnglobant_.setPosition(16, 32);
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
	vit_ = vitM_ = 30;

	regenARM_ = 0;
	regenBOU_ = 0;
	regenPV_ = 0;

	degatsColl_ = 50;

	// Initialisation de la trajectoire
	trajectoire_ = traj;
	params_.push_back((float)param1);
	params_.push_back((float)param2);
	params_.push_back((float)param3);
	params_.push_back((float)param4);

}

void VaisseauEclaireur::gestion(proj_container proj_cont, Input& input)
{
	// Juste pour mute les warnings du compilateur
	(void)input;
	
	/*if (frames_%100==0)
	{
		params_[0] = -params_[0];
		posInit_ = position_;
		t_ = 0;
		frames_ = 0;
	}*/
	
	if (actif_)
	{
		setPosition(traj_position(trajectoire_, t_age_.asMilliseconds(), vit_, posInit_, params_));
		afficher(debug_);

		t_age_ += ecran_.getClock().getElapsedTime();		
	}
}

