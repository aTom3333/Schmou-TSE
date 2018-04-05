#include "VaisseauEclaireur.h"
#include <cmath>

#include <iostream>


VaisseauEclaireur::VaisseauEclaireur(Ecran &ecran, float x, float y,Trajectoire traj, double param1, double param2, double param3, double param4) :
	Vaisseau(ecran)
{
	// Sprites
	sprites_.emplace_back(*ecran_.getChargeur().getTexture("vaiss.ennemi.test"));
	for (auto& sprite : sprites_)
		sprite.setOrigin({ this->getTaille().x / 2.0f, this->getTaille().y / 2.0f });

	// Cercle englobant
	//TODO PG Englobeur
	const float R = hypot(this->getTaille().x / 2.0f, this->getTaille().y / 2.0f);
	cercleEnglobant_ = sf::CircleShape(R);
	cercleEnglobant_.setOrigin(R, R);

	//Hitbox
	forme_.emplace_back(new sf::CircleShape(cercleEnglobant_));
	for (auto& forme : forme_)
		forme->setOrigin(forme->getGlobalBounds().width / 2.0f, forme->getGlobalBounds().height / 2.0f);

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

	regenArmure_ = 0;
	regenBouclier_ = 0;
	regenPv_ = 0;

	degatsCollision_ = 50;

	// Initialisation de la trajectoire
	trajectoire_ = traj;
	params_.push_back((float)param1);
	params_.push_back((float)param2);
	params_.push_back((float)param3);
	params_.push_back((float)param4);

	// Position initiale
	setPosition({ x, y });
	posInit_ = getPosition();

}

void VaisseauEclaireur::gestion(proj_container &proj_cont, Input& input)
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
		t_age_ += ecran_.getTempsFrame();
		setPosition(traj_position(trajectoire_, t_age_, vit_, posInit_, params_));
		afficher();
	}
}

