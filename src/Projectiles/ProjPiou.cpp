#include "ProjPiou.h"
#include <cmath>

ProjPiou::ProjPiou(Ecran& ecran, std::shared_ptr<Entite> lanceur, std::vector<sf::Sprite>& sprite, std::vector<sf::Sound>& sound, Equipe equipe) :
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
	if(!sounds_.empty())sounds_.front().play();//son joué à la création du projectile	

	// Cercle englobant
    //TODO utiliser la fonction Englobeuse
	cercleEnglobant_ = sf::CircleShape(hypot(20,30));
	cercleEnglobant_.setOrigin(10, 10);
	cercleEnglobant_.setPosition(10, 10);
    
    //Hitbox
	forme_.emplace_back(new sf::RectangleShape({20,30}));
    forme_.at(0)->setOrigin({10,15});
	
	// Caractéristiques
	equipe_ = equipe;

	//Stats
	pv_ = pvM_ = 10;
	armure_ = armureM_ = 0;
	bouclier_ = bouclierM_ = 0;

	regenARM_ = regenBOU_ = regenPV_ = 0;

	degatsColl_ = 70; //TODO PG multiplier par lanceur.stats().atk (faire un genre de struct stats)

	vit_ = vitM_ = 700;

	//position de départ
	setPosition({ lanceur->getPosition().x ,  lanceur->getPosition().y - lanceur->getTaille().y / 2.0f });
}

void ProjPiou::gestion()
{
	auto& window = ecran_.getWindow();
	auto tempsEcoule = ecran_.getClock().getElapsedTime();
	move();
	window.draw(sprites_.at(0));//HACK PG il faut màj afficher de entité avec sprites_ puis le mettre ici
}

void ProjPiou::agit(Entite& proj)
{
	proj.recoitDegats(degatsColl_);
	detruit_ = true;
}
