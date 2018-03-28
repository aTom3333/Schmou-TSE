#include "ProjBoing.h"
#include "../constantes.h"

#include <cmath>


ProjBoing::ProjBoing(Ecran& ecran, std::shared_ptr<Entite> lanceur, std::vector<sf::Sprite>& sprite, std::vector<sf::Sound>& sound, Equipe equipe) :
	Projectile(ecran)
{
	// Weak pointeur vers lanceur
	lanceur_ = lanceur;

	// Gestion du sprite
	sprites_ = sprite;

	//Origines
	origine_ = { 16,16 }; //basé sur image ballePaques(32x32)
	sprites_.at(0).setOrigin({ 16,16 });

	//Gestion du son
	sounds_ = sound;
	if (!sounds_.empty())sounds_.front().play();//son joué à la création du projectile	

												// cercle englobant
												//TODO utiliser la fonction Englobeuse
	cercleEnglobant_ = sf::CircleShape(hypot(16, 16));
	cercleEnglobant_.setOrigin(16, 16);
	cercleEnglobant_.setPosition(16, 16);

	//Hitbox
	forme_.emplace_back(new sf::RectangleShape({ 16,16 }));
	forme_.at(0)->setOrigin({ 16,16 });

	// Caractéristiques
	equipe_ = equipe;

	//Stats
	pv_ = pvM_ = 10;
	armure_ = armureM_ = 0;
	bouclier_ = bouclierM_ = 0;

	regenARM_ = regenBOU_ = regenPV_ = 0;

	degatsColl_ = 30; //TODO PG xlanceur.stats().atk

	vit_ = vitM_ = 400;
	rotation_ = rand() % 100 / 100 * 2 * PI; // TODO CL rand c++

	rayon_ = 32.f;

	//position de départ
	setPosition({ lanceur->getPosition().x + rayon_*cos(rotation_),  lanceur->getPosition().y + rayon_*cos(rotation_) });
}


ProjBoing::~ProjBoing()
{
}

void ProjBoing::gestion()
{
	auto& window = ecran_.getWindow();
	auto tempsEcoule = ecran_.getClock().getElapsedTime();
	move();

	rotation_ += 100 * tempsEcoule.asSeconds();
	sprites_.at(0).setRotation(rotation_);

	window.draw(sprites_.at(0));//HACK PG màj affocher de entité avec sprites_ puis changer ici
}

void ProjBoing::agit(Entite& proj)
{
	proj.recoitDegats(degatsColl_);
	detruit_ = true;
}

