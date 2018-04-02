#include "ProjMissile.h"
#include <cmath>



ProjMissile::ProjMissile(Ecran& ecran, std::shared_ptr<Entite> lanceur, std::vector<sf::Sprite>& sprite, std::vector<sf::Sound>& sound, Equipe equipe, const bool& aimbot) :
	Projectile(ecran)
{
	// Weak pointeur vers lanceur
	lanceur_ = lanceur;

	// Gestion du sprite
	sprites_ = sprite;

	//Origines
	origine_ = { 20,40 }; //basé sur projectile_missile de dimensions 40x80
	sprites_.at(0).setOrigin({ 20,40 });

	//Gestion du son
	sounds_ = sound;
	if (!sounds_.empty())sounds_.front().play();//son joué à la création du projectile	

	// cercle englobant
	//TODO utiliser la fonction Englobeuse
	const float R = hypot(20, 40);//basé sur projectile_missile de dimensions 40x80
	cercleEnglobant_ = sf::CircleShape(R);
	cercleEnglobant_.setOrigin(R, R);

	//Hitbox
	forme_.emplace_back(new sf::RectangleShape({ 40,80 }));
	forme_.at(0)->setOrigin({ 20,40 });

	// Caractéristiques
	equipe_ = equipe;
	aimbot_ = aimbot;
	if (aimbot_)
	{
		for (auto vaisseau : ecran_.getVaisseauxContainer())
		{
			//TODO PG récupérer position des vaisseaux de l'écran ?
			//auto pos = vaisseau->getPosition();
			if(auto cible
		}
	}

	//Stats
	pv_ = pvM_ = 10;
	armure_ = armureM_ = 0;
	bouclier_ = bouclierM_ = 0;

	regenArmure_ = regenBouclier_ = regenPv_ = 0;

	degatsCollision_ = 300; //TODO PG xlanceur.stats().atk

	vit_ = vitM_ = 10;

	//position de départ
	setPosition({ lanceur->getPosition().x ,  lanceur->getPosition().y - lanceur->getTaille().y / 2.0f });

    actif_ = true;

	coef_acceleration_ = 1.05;

	rotation_ = -PI / 2;
}

void ProjMissile::gestion()
{
	auto& window = ecran_.getWindow();
	auto tempsEcoule = ecran_.getTempsFrame();

	if (!aimbot_)
	{
		vit_ *= coef_acceleration_ * (1. + tempsEcoule.asSeconds());
		if (vit_ >= 1000) vit_ = 1000;

		move();
		afficher();
	}
	else
	{

	}
}

void ProjMissile::agit(Entite & e)
{
    e.recoitDegats(degatsCollision_);
    detruit_ = true;
}
