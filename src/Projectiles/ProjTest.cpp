#include "ProjTest.h"
#include "../constantes.h"

ProjTest::ProjTest()
{

	//sprite
	texture_.loadFromFile("../../rc/Sprites/base/balle.png");
	sprite_.setTexture(texture_);

	//hitbox simple (et complète dans ce cas car c'est le projectile est un cercle)
	cercleEnglobant_ =  sf::CircleShape(16);
	cercleEnglobant_.setOrigin(16, 16);
	forme_.emplace_back(new sf::CircleShape(cercleEnglobant_));

	//attributs
	age_ = 0;

	pvMax_ = 10;
	armureMax_ = 0;
	bouclierMax_ = 0;

	pv_ = pvMax_;
	armure_ = armureMax_;
	bouclier_ = bouclierMax_;

	regenARM_ = regenBOU_ = regenPV_ = 0;

	degats_ = 10;

	// Multiplicateur de direction (1 vers la droite/bas -1 vers le haut/gauche)
	mx_ = rand() % 2 == 0 ? 1 : -1;
	my_ = rand() % 2 == 0 ? 1 : -1;

	// Vitesse entre 3 et 8
	vx_ = rand() % 5 + 3;
	vy_ = rand() % 5 + 3;

	float x = rand() % 800, y = rand() % 600;

	setPosition({ x,  y});
}

ProjTest::ProjTest(int x, int y)
{
	//Sprite
	texture_.loadFromFile("../../rc/Sprites/base/balle.png");
	sprite_.setTexture(texture_);

	//hitbox simple (et complète dans ce cas car c'est le projectile est un cercle)
	cercleEnglobant_ = sf::CircleShape(16);
	cercleEnglobant_.setOrigin(16, 16);
	cercleEnglobant_.setPosition(16,16);

	forme_.emplace_back(new sf::CircleShape(cercleEnglobant_));
	
	//attributs
	age_ = 0;

	//stats

	pvMax_ = 10;
	armureMax_ = 0;
	bouclierMax_ = 0;

	pv_ = pvMax_;
	armure_ = armureMax_;
	bouclier_ = bouclierMax_;

	regenARM_ = regenBOU_ = regenPV_ = 0;

	degats_ = 50;
	actif_ = true;

	// Multiplicateur de direction (1 vers la droite/bas -1 vers le haut/gauche)
	mx_ = rand() % 2 == 0 ? 1 : -1;
	my_ = rand() % 2 == 0 ? 1 : -1;

	// Vitesse entre 3 et 8
	vx_ = rand() % 5 + 3;
	vy_ = rand() % 5 + 3;

	vit_ = 1;

	float x1 = x + 40*mx_, y1 = y + 40 * my_;

	setPosition({ x1,  y1 });
}


ProjTest::~ProjTest()
{
}

void ProjTest::gestion(sf::RenderWindow& window)
{
	age_++;

	// Modification de la postion
	setPosition({ position_.x + vit_*vx_*mx_, position_.y + vit_*vy_*my_ });

	// Gestion du rebond
	if (position_.x > ECRAN_L - 32 - 1)
	{
		position_.x = ECRAN_L - 32 - 1;
		mx_ = -1;
	}
	if (position_.x < 1)
	{
		position_.x = 1;
		mx_ = 1;
	}
	if (position_.y > ECRAN_H - 32 - 1)
	{
		position_.y = ECRAN_H - 32 - 1;
		my_ = -1;
	}
	if (position_.y < 1)
	{
		position_.y = 1;
		my_ = 1;
	}

	// Afficher le projectile
	afficher(window);
}

void ProjTest::agit(Entite& proj)
{
	proj.recoitDegats(degats_);
	detruit_ = true;
}

