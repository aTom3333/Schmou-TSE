#include "ProjPiou.h"

/**
* @fn ProjTest
* @brief Constructeur
*
* Vide
*/

ProjPiou::ProjPiou()
{
}

/**
* @fn ProjTest
* @brief Constructeur
* @param x Abscisse de la postion de départ du projectile
* @param y Ordonnée de la postion de départ du projectile
*
* Créer un projectile piou à la position donnée en paramètre
*/

ProjPiou::ProjPiou(int x, int y)
{
	// Projectile n'intéragit pas avec les autres projectiles
	collisionable_ = false;

	// Gestion du sprite
	texture_.loadFromFile("../../rc/Sprites/base/projectile_test.png");
	sprite_.setTexture(texture_);

	// Hitbox
	cercleEnglobant_ = sf::CircleShape(10);
	cercleEnglobant_.setOrigin(10, 10);
	
	age_ = 0;

	//  Projectile qui se déplace verticalement
	vx_ = 0;
	vy_ = -8;

	float x1 = x, y1 = y;

	setPosition({ x1,  y1 });
}

/**
* @fn ~ProjTest
* @brief Destructeur
*
* Vide
*/
ProjPiou::~ProjPiou()
{
}

/**
* @fn gestion
* @brief Gestion du projectile
* @param window Fenetre de jeu
*
* Gestion du déplacement et de l'affichage
*/

void ProjPiou::gestion(sf::RenderWindow & window)
{
	setPosition({ position_.x, position_.y + vy_});
	afficher(window);
}
