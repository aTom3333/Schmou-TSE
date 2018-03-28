#include "ProjMissile.h"
#include <cmath>


ProjMissile::ProjMissile(Ecran& ecran, std::shared_ptr<Entite> lanceur, std::vector<sf::Sprite>& sprite, std::vector<sf::Sound>& sound, Equipe equipe) :
	ProjMissile(ecran, lanceur)
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
	cercleEnglobant_ = sf::CircleShape(hypot(20, 40));
	cercleEnglobant_.setOrigin(20, 40);
	cercleEnglobant_.setPosition(20, 40);

	//Hitbox
	forme_.emplace_back(new sf::RectangleShape({ 40,80 }));
	forme_.at(0)->setOrigin({ 20,40 });

	// Caractéristiques
	equipe_ = equipe;

	//Stats
	pv_ = pvM_ = 10;
	armure_ = armureM_ = 0;
	bouclier_ = bouclierM_ = 0;

	regenARM_ = regenBOU_ = regenPV_ = 0;

	degatsColl_ = 300; //TODO PG xlanceur.stats().atk

	vit_ = vitM_ = 700;

	//position de départ
	setPosition({ lanceur->getPosition().x ,  lanceur->getPosition().y - lanceur->getTaille().y / 2.0f });

    actif_ = true;

	coef_acceleration_ = 1.05;
}

void ProjMissile::gestion()
{
	auto& window = ecran_.getWindow();
	auto tempsEcoule = ecran_.getClock().getElapsedTime();

	vit_ *= coef_acceleration_ * tempsEcoule.asMilliseconds();
	if (vit_ >= 400) vit_ = 400;

	move();
	window.draw(sprites_.at(0));//HACK PG il faut màj afficher de entité avec sprites_ puis le mettre ici
}

void ProjMissile::agit(Entite & e)
{
    e.recoitDegats(degatsColl_);
    detruit_ = true;
}
