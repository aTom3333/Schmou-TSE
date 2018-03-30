#include "VaisseauDefenseur.h"

#include <cmath>


VaisseauDefenseur::VaisseauDefenseur(Ecran& ecran, float x, float y, vaisseau_container &vaisseaux, Trajectoire traj, float param1, float param2, float param3, float param4) : 
	Vaisseau(ecran)
{
	// Sprites
	sprites_.emplace_back(*ecran_.getChargeur().getTexture("vaiss.defenseur"));
	for (auto& sprite : sprites_)
		sprite.setOrigin({ this->getTaille().x / 2.0f, this->getTaille().y / 2.0f });

	// Cercle englobant
	//TODO PG Englobeur
	const float R = hypot(this->getTaille().x / 2.0f, this->getTaille().y / 2.0f);
	cercleEnglobant_ = sf::CircleShape(R);
	cercleEnglobant_.setOrigin(R, R);

	//Hitbox
	forme_.emplace_back(new sf::RectangleShape({ 128,64 }));
	for (auto& forme : forme_)
		forme->setOrigin(forme->getGlobalBounds().width/2.0f, forme->getGlobalBounds().height/2.0f);

	//Origine
	origine_ = { this->getTaille().x / 2.0f, this->getTaille().y / 2.0f };

	// Caractéristiques de code
	equipe_ = ENNEMI;
	actif_ = false;
	invincibilable_ = false;

	// Stats
	pv_ = pvM_ = 100;
	armure_ = armureM_ = 50;
	bouclier_ = bouclierM_ = 0;
	vit_ = vitM_ = 200;

	regenARM_ = 0;
	regenBOU_ = 0;
	regenPV_ = 0;

	degatsColl_ = 75;

	// Composition
	//ajout d'un bouclier
	annexes_.emplace_back(new VaissBouclier(ecran));
	annexes_.at(0)->setOrigin(annexes_.at(0)->getOrigin() + sf::Vector2f({ 0, -(this->getTaille().y + annexes_.at(0)->getTaille().y) / 2.0f }));
	vaisseaux.push_back(annexes_[0]);

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

void VaisseauDefenseur::gestion(proj_container &proj_cont, Input& input)
{
	/*if (frames_%100==0)
	{
	params_[0] = -params_[0];
	posInit_ = position_;
	t_ = 0;
	frames_ = 0;
	}*/

	if (actif_)
	{
		setPosition(traj_position(trajectoire_, t_age_, vit_, posInit_, params_));
		afficher();

		// Gestion du module de bouclier
		for (auto& annexe : annexes_)
		{
			annexe->setActif(true);
			annexe->setPosition({ position_.x, position_.y });
			annexe->gestion(proj_cont, input);
		}

		t_age_ += ecran_.getTempsFrame();
	}
	
}

void VaisseauDefenseur::destruction()
{
	for (auto& annexe : annexes_) annexe->setDetruit(true);
	detruit_ = true;
}