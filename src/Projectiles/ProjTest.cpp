#include "ProjTest.h"
#include "../constantes.h"

/**
* @fn ProjTest
* @brief Constructeur
*
* Cr�er un projectile de test � une postion al�atoire
*/

ProjTest::ProjTest()
{

	//sprite
	texture_.loadFromFile("../../rc/Sprites/base/balle.png");
	sprite_.setTexture(texture_);

	//hitbox simple (et compl�te dans ce cas car c'est le projectile est un cercle)
	cercleEnglobant_ =  sf::CircleShape(16);
	cercleEnglobant_.setOrigin(16, 16);

	//attributs
	age_ = 0;

	// Multiplicateur de direction (1 vers la droite/bas -1 vers le haut/gauche)
	mx_ = rand() % 2 == 0 ? 1 : -1;
	my_ = rand() % 2 == 0 ? 1 : -1;

	// Vitesse entre 3 et 8
	vx_ = rand() % 5 + 3;
	vy_ = rand() % 5 + 3;
	

	float x = rand() % 800, y = rand() % 600;

	setPosition({ x,  y});
}

/**
* @fn ProjTest
* @brief Constructeur
* @param x Abscisse de la postion de d�part du projectile
* @param y Ordonn�e de la postion de d�part du projectile
*
* Cr�er un projectile de test � la position donn�e en param�tre
*/

ProjTest::ProjTest(int x, int y)
{
	//Sprite
	texture_.loadFromFile("../../rc/Sprites/base/balle.png");
	sprite_.setTexture(texture_);

	//hitbox simple (et compl�te dans ce cas car c'est le projectile est un cercle)
	cercleEnglobant_ = sf::CircleShape(16);
	cercleEnglobant_.setOrigin(16, 16);
	
	//attributs
	age_ = 0;

	// Multiplicateur de direction (1 vers la droite/bas -1 vers le haut/gauche)
	mx_ = rand() % 2 == 0 ? 1 : -1;
	my_ = rand() % 2 == 0 ? 1 : -1;

	// Vitesse entre 3 et 8
	vx_ = rand() % 5 + 3;
	vy_ = rand() % 5 + 3;

	float x1 =x, y1 = y;

	setPosition({ x1,  y1 });
}

/**
* @fn ~ProjTest
* @brief Destructeur
*
* Vide
*/

ProjTest::~ProjTest()
{
}

/**
* @fn gestion
* @brief Gestion du projectile
* @param window Fenetre de jeu
*
* Gestion du d�placement et de la collision avec les bords
*/

void ProjTest::gestion(sf::RenderWindow& window)
{
	age_++;

	// Modification de la postion
	setPosition({ position_.x + vx_*mx_, position_.y + vy_*my_ });

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

