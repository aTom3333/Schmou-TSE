#include "ProjBoing.h"
#include "../constantes.h"

ProjBoing::ProjBoing()
{
}

ProjBoing::ProjBoing(int x, int y, sf::Sound sound)
{
	//Sprite
	texture_.loadFromFile("../../rc/Sprites/base/ballePaques.png");
	sprite_.setTexture(texture_);

	//son
	sound_ = sound;

	//hitbox simple (et complète dans ce cas car c'est le projectile est un cercle)
	cercleEnglobant_ = sf::CircleShape(16);
	cercleEnglobant_.setOrigin(16, 16);
	cercleEnglobant_.setPosition(16,16);

	sprite_.setOrigin(16, 16);

	forme_.emplace_back(new sf::CircleShape(cercleEnglobant_));
	
	//attributs

	//stats

	pvM_ = 10;
	armureM_ = 0;
	bouclierM_ = 0;

	pv_ = pvM_;
	armure_ = armureM_;
	bouclier_ = bouclierM_;

	regenARM_ = regenBOU_ = regenPV_ = 0;

	degatsColl_ = 50;
	actif_ = true;

	// Multiplicateur de direction (1 vers la droite/bas -1 vers le haut/gauche)
	mx_ = rand() % 2 == 0 ? 1 : -1;
	my_ = rand() % 2 == 0 ? 1 : -1;

	// Vitesse entre 30 et 80
	vx_ = (rand() % 5 + 3);
	vy_ = (rand() % 5 + 3);

	vit_ = 100;

	float x1 = x + 40*mx_, y1 = y + 40 * my_;

	setPosition({ x1,  y1 });
	equipe_ = NEUTRE;
	rotation_ = 0;
}


ProjBoing::~ProjBoing()
{
}

void ProjBoing::gestion(sf::RenderWindow& window, sf::Time tempsEcoule)
{
	// Modification de la position
	setPosition({ position_.x + vit_*vx_*mx_*tempsEcoule.asSeconds(), position_.y + vit_*vy_*my_*tempsEcoule.asSeconds() });

	// Gestion du rebond
	if (position_.x > ECRAN_L - 32 - 1)
	{
		position_.x = ECRAN_L - 32 - 1;
		mx_ = -1;
		sound_.play();
	}
	if (position_.x < 1)
	{
		position_.x = 1;
		mx_ = 1;
		sound_.play();
	}
	if (position_.y > ECRAN_H - 32 - 1)
	{
		position_.y = ECRAN_H - 32 - 1;
		my_ = -1;
		sound_.play();
	}
	if (position_.y < 1)
	{
		position_.y = 1;
		my_ = 1;
		sound_.play();
	}

	rotation_ += 20;
	sprite_.setRotation(rotation_);

	// Afficher le projectile
	afficher(window);
}

void ProjBoing::agit(Entite& proj)
{
	proj.recoitDegats(degatsColl_);
	detruit_ = true;
}

