#include "ProjPiou.h"
#include <cmath>

ProjPiou::ProjPiou(Ecran& ecran, std::shared_ptr<Entite> lanceur, std::vector<sf::Sprite>& sprite, std::vector<sf::Sound>& sound, Equipe equipe) :
	Projectile(ecran)
{	
    // Weak pointeur vers lanceur
    lanceur_ = lanceur;
    
	// Gestion du sprite
	sprites_ = sprite;

	// Origines
	origine_ = { 10,15 }; //basé sur image Piou20x30
	sprites_.at(0).setOrigin({ 10,15 });

	// Gestion du son
	sounds_ = sound;
	sounds_.front().play(); //son joué à la création du projectile	

	// Cercle englobant
    //TODO utiliser la fonction Englobeuse
	const float R = hypot(10, 15); //basé sur Piou20x30
	cercleEnglobant_ = sf::CircleShape(R);
	cercleEnglobant_.setOrigin(R, R);
    
    //Hitbox
	forme_.emplace_back(new sf::RectangleShape({20,30}));
    forme_.at(0)->setOrigin({10,15}); //basé sur Piou20x30
	
	// Caractéristiques
	equipe_ = equipe;

	//Stats
	pv_ = pvM_ = 10;
	armure_ = armureM_ = 0;
	bouclier_ = bouclierM_ = 0;

	regenArmure_ = regenBouclier_ = regenPv_ = 0;

	degatsCollision_ = 70; //TODO PG multiplier par lanceur.stats().atk (faire un genre de struct stats)

	vit_ = vitM_ = 700;

	//position de départ
	setPosition({ lanceur->getPosition().x ,  lanceur->getPosition().y - lanceur->getTaille().y / 2.0f });
}

void ProjPiou::gestion()
{
	auto& window = ecran_.getWindow();
	auto tempsEcoule = ecran_.getTempsFrame();
	move();
	afficher();
}

void ProjPiou::agit(Entite& proj)
{
	proj.recoitDegats(degatsCollision_);
	detruit_ = true;
}
