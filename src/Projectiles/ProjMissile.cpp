#include "ProjMissile.h"
#include "../Vaisseau/Vaisseau.h"
#include <cmath>


#include <iostream>

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
	if (equipe_ == ENNEMI) rotate(180); //TODO PG projectiles ennemis retournés : à implémenter à partir de roation du lanceur et vaisseaux ennemis déjà retournés
	aimbot_ = aimbot;

	// Caractéristiques spécifiques
	t_acceleration_ = sf::milliseconds(2000);//temps pour atteindre vitesse max

	//Stats
	pv_ = pvM_ = 10;
	armure_ = armureM_ = 0;
	bouclier_ = bouclierM_ = 0;

	regenArmure_ = regenBouclier_ = regenPv_ = 0;

	degatsCollision_ = 300; //TODO PG xlanceur.stats().atk

	vit_ = vitM_ = 1000;

	//position de départ
	setPosition({ lanceur->getPosition().x ,  lanceur->getPosition().y - lanceur->getTailleSprite().y / 2.0f });

	//Aimbot
	if (aimbot_)
	{
		float distance_min = std::numeric_limits<float>::max();
		for (auto& vaisseau : ecran_.getVaisseauxContainer())
		{
			if (vaisseau->getEquipe() != equipe_ && vaisseau->isActif())
			{
				auto pos = vaisseau->getPosition();
				if (hypot(pos.x - position_.x, pos.y - position_.y) < distance_min)
				{
					distance_min = hypot(pos.x - position_.x, pos.y - position_.y);
					cible_ = vaisseau;
				}
			}
		}
	}

}

void ProjMissile::gestion()
{
	auto& window = ecran_.getWindow();
	auto tempsEcoule = ecran_.getTempsFrame();

	vit_ = vitM_ * pow(expm1(t_age_ / t_acceleration_), 2);
	if (vit_ > vitM_)vit_ = vitM_;

	//affiche valeurs vitesses possibles, voir métadocuments
	//std::cerr << "age : "<<t_age_.asMilliseconds() << "   sqrt : " << vitM_ * sqrt(t_age_ / t_acceleration_)<< "   lin : " << vitM_ * t_age_ / t_acceleration_ << "   exp : " << vit_ << std::endl;

	vaisseau_ptr cible;
	if (aimbot_)
	{
		if (auto cible = cible_.lock())
		{
			if (!cible->estDetruit())
			{
				float vit_angulaire = 100 * ecran_.getTempsFrame().asSeconds();//degrés par seconde
				float X = cible->getPosition().x - position_.x;
				float Y = cible->getPosition().y - position_.y;
				float angleTot = atan2(-Y, -X) * 180 / PI ; //angle avec cible

				if (angleTot < 0) angleTot += 360;

				int mult = -1;
				if (rotation_ < angleTot || (rotation_ - angleTot >= 180 )) mult = +1;

				float angle = abs(rotation_ - angleTot) < vit_angulaire ? angleTot - rotation_ : mult * vit_angulaire; // angle est le maximum entre l'angle avce la cible et la vitesse angulaire max

				rotate(angle); //ciblage parfait

			}
			else //nouvelle cible
			{
				// TODO CL Pas de nouvelle cible ?
				float distance_min = std::numeric_limits<float>::max();
				for (auto& vaisseau : ecran_.getVaisseauxContainer())
				{
					if (vaisseau->getEquipe() != equipe_ && vaisseau->isActif())
					{
						auto pos = vaisseau->getPosition();
						if (hypot(pos.x - position_.x, pos.y - position_.y) < distance_min)
						{
							distance_min = hypot(pos.x - position_.x, pos.y - position_.y);
							cible_ = vaisseau;
						}
					}
				}
			}
		}
		else
		{
			aimbot_ = false; //sécurité si pas de cible
		}
	}

	t_age_ += ecran_.getTempsFrame();
	move();
	afficher();

	if (t_age_ > sf::seconds(10)) detruit_ = true;
}

void ProjMissile::agit(Entite & e)
{
    e.recoitDegats(degatsCollision_);
    detruit_ = true;
}
