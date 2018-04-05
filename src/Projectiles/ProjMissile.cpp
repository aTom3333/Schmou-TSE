#include "ProjMissile.h"
#include "../Vaisseau/Vaisseau.h"
#include <cmath>

template <typename T> int signe(T val) {
	return (T(0) < val) - (val < T(0));
}


ProjMissile::ProjMissile(Ecran& ecran, std::shared_ptr<Entite> lanceur, std::vector<sf::Sprite>& sprite, std::vector<sf::Sound>& sound, Equipe equipe, bool aimbot) :
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
		float distance_min = std::numeric_limits<float>::max();
		for (auto& vaisseau : ecran_.getVaisseauxContainer())
		{
			auto pos = vaisseau->getPosition();
			if (hypot(pos.x - position_.x, pos.y - position_.y) < distance_min)
				cible_ = vaisseau;
		}
	}

	// Caractéristiques spécifiques
	coef_acceleration_ = 1.05;

	//Stats
	pv_ = pvM_ = 10;
	armure_ = armureM_ = 0;
	bouclier_ = bouclierM_ = 0;

	regenArmure_ = regenBouclier_ = regenPv_ = 0;

	degatsCollision_ = 300; //TODO PG xlanceur.stats().atk

	vit_ = vitM_ = 10;

	//position de départ
	setPosition({ lanceur->getPosition().x ,  lanceur->getPosition().y - lanceur->getTaille().y / 2.0f });

}

void ProjMissile::gestion()
{
	auto& window = ecran_.getWindow();
	auto tempsEcoule = ecran_.getTempsFrame();


	vit_ *= coef_acceleration_ * (1. + tempsEcoule.asSeconds());
	if (vit_ >= 1000) vit_ = 1000;

	vaisseau_ptr cible;
	if (aimbot_)
	{
		if (auto cible = cible_.lock())
		{
			float X = cible->getPosition().x - position_.x;
			if (X)
			{
				float Y = cible->getPosition().y - position_.y;
				float angle = tan(X / Y);
				this->rotate(std::max(angle, 2.f * signe(angle)));
			}
			else
			{
				this->rotate(PI / 2.f * signe(cible->getPosition().y - position_.y));
			}
		}
	}

	move();
	afficher();
}

void ProjMissile::agit(Entite & e)
{
    e.recoitDegats(degatsCollision_);
    detruit_ = true;
}
