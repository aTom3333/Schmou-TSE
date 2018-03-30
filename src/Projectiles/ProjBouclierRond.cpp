#include "ProjBouclierRond.h"
#include <cmath>

ProjBouclierRond::ProjBouclierRond(Ecran& ecran, std::shared_ptr<Entite> lanceur, std::vector<sf::Sprite>& sprite, std::vector<sf::Sound>& sound, Equipe equipe):
	Projectile(ecran)
{
	// Weak pointeur vers lanceur
	lanceur_ = lanceur;

	// Gestion du sprite
	sprites_ = sprite;

	//Origines
	origine_ = { 10,15 }; //basé sur image Piou20x30
	sprites_.at(0).setOrigin({ 10,15 });

	//Gestion du son
	sounds_ = sound;
	if (!sounds_.empty())sounds_.front().play();//son joué à la création du projectile	

												// cercle englobant
												//TODO utiliser la fonction Englobeuse
	cercleEnglobant_ = sf::CircleShape(75);
	cercleEnglobant_.setOrigin(75, 75);
	cercleEnglobant_.setPosition(75, 75);

	//Hitbox
	forme_.emplace_back(new sf::CircleShape(cercleEnglobant_));
	forme_.at(0)->setOrigin({ 75,75 });

	// Caractéristiques de code
	equipe_ = equipe;
	actif_ = true;
	invincibilable_ = false;

	//Stats
	pv_ = pvM_ = 500;
	armure_ = armureM_ = 0;
	bouclier_ = bouclierM_ = 0;

	regenARM_ = regenBOU_ = regenPV_ = 0;

	degatsColl_ = 0; //TODO PG xlanceur.stats().atk

	vit_ = vitM_ = 700;

	//position de départ
	setPosition({ lanceur->getPosition().x ,  lanceur->getPosition().y });

	tempsMax_ = 1000;
}

void ProjBouclierRond::gestion()
{
	auto& window = ecran_.getWindow();
	auto tempsEcoule = ecran_.getTempsFrame();
	
	if (auto lanceur = lanceur_.lock())
	{
		setPosition({ lanceur->getPosition().x, lanceur->getPosition().y });

		window.draw(sprites_.at(0));//HACK PG màj affocher de entité avec sprites_ puis changer ici

		if (tempsEcoule.asMilliseconds() > tempsMax_)
			detruit_ = true;
	}
}


void ProjBouclierRond::agit(Entite& proj)
{
	proj.recoitDegats(degatsColl_);
	pv_ -= proj.getDegatsColl_();
	int alpha = (int)(pv_ / pvM_ * 255);
	sprites_.front().setColor({ 255, 255, 255, ( sf::Uint8)alpha });
	if (pv_ < 0)
		detruit_ = true;
}