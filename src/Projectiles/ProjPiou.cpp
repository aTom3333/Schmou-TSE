#include "ProjPiou.h"
#include <cmath>

ProjPiou::ProjPiou(const Entite& lanceur, std::vector<sf::Sprite>& spriteV, std::vector<std::shared_ptr<sf::Texture>>& textureV, sf::Sound& sound, Equipe equipe)
{	
	// Gestion du sprite
	textureV_ = textureV;
	spriteV_ = spriteV;

	//Origines
	origine_ = { 10,15 }; //basé sur image Piou20x30
	spriteV_.at(0).setOrigin({ 10,15 });

	//Gestion du son
	sound_ = sound;
	sound.play();//son joué à la création du projectile	

	// Hitbox
	cercleEnglobant_ = sf::CircleShape(hypot(20,30));
	cercleEnglobant_.setOrigin(10, 10);
	cercleEnglobant_.setPosition(10, 10);
	forme_.emplace_back(new sf::RectangleShape({20,30}));
	
	// Caractéristiques
	equipe_ = equipe;
	actif_ = true;

	//Stats
	pv_ = pvM_ = 10;
	armure_ = armureM_ = 0;
	bouclier_ = bouclierM_ = 0;

	regenARM_ = regenBOU_ = regenPV_ = 0;

	degatsColl_ = 70;

	vit_ = vitM_ = 700;

	//position de départ
	setPosition({ lanceur.getPosition().x ,  lanceur.getPosition().y - lanceur.getTaille().y / 2.0f });
}

ProjPiou::~ProjPiou()
{
}

void ProjPiou::gestion(sf::RenderWindow & window, sf::Time tempsEcoule)
{
	move({ 0,-vit_ * tempsEcoule.asSeconds() });
	window.draw(spriteV_.at(0));//HACK PG màj affocher de entité avec spriteV_ puis changer ici
}

void ProjPiou::agit(Entite& proj)
{
	proj.recoitDegats(degatsColl_);
	detruit_ = true;
}
