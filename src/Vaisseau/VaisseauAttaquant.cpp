#include "VaisseauAttaquant.h"
#include <cmath>

#include<iostream>


VaisseauAttaquant::VaisseauAttaquant(Ecran& ecran, float x, float y, Trajectoire traj, float param1, float param2, float param3, float param4) : 
	Vaisseau(ecran)
{
	// Sprites
	sprites_.emplace_back(*ecran_.getChargeur().getTexture("vaiss.attaquant"));
	for (auto& sprite : sprites_)
		sprite.setOrigin({ this->getTailleSprite().x / 2.0f, this->getTailleSprite().y / 2.0f });

	// Cercle englobant
	//TODO PG Englobeur
	const float R = hypot(this->getTailleSprite().x / 2.0f, this->getTailleSprite().y / 2.0f);
	cercleEnglobant_ = sf::CircleShape(R);
	cercleEnglobant_.setOrigin(R, R);

	//Hitbox
	forme_.emplace_back(new sf::RectangleShape({ this->getTailleSprite().x, this->getTailleSprite().y}));
	for (auto& forme : forme_)
		forme->setOrigin(forme->getGlobalBounds().width / 2.0f, forme->getGlobalBounds().height / 2.0f);

	//Origine
	origine_ = { this->getTailleSprite().x / 2.0f, this->getTailleSprite().y / 2.0f };

	// Caractéristiques de code
	equipe_ = ENNEMI;
	actif_ = false;

	// Stats
	pv_ = pvM_ = 300;
	armure_ = armureM_ = 200;
	bouclier_ = bouclierM_ = 0;
	vit_ = vitM_ = 300;

	regenArmure_ = 0;
	regenBouclier_ = 0;
	regenPv_ = 0;

	degatsCollision_ = 50;

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
		if (t_age_.asMilliseconds() > n_ * 2000)
		{
			capacites_[0]->utiliser(proj_cont);
			n_++;
			//t_age_ = sf::Time::Zero;
		}

		setPosition(traj_position(trajectoire_,t_age_, vit_, posInit_, params_));
		afficher();

		t_age_ += ecran_.getTempsFrame();
	}

}

