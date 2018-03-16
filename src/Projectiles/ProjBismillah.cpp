#include "ProjBismillah.h"



ProjBismillah::ProjBismillah(int x, int y, sf::Sound sound, Equipe equipe)
{
	// Gestion du sprite
	texture_.loadFromFile("../../rc/Sprites/Capacites/Piou20x30.PNG");
	//sf::RectangleShape texture({ 32, 128 });
	sprite_.setTexture(texture_);

	////Gestion du son
	sound_.play();

	// Hitbox
	cercleEnglobant_ = sf::CircleShape(5);
	cercleEnglobant_.setOrigin(10, 10);
	cercleEnglobant_.setPosition(10, 10);
	forme_.emplace_back(new sf::RectangleShape({ 20,30 }));

	// Caractéristiques
	equipe_ = equipe;
	age_ = 0;
	actif_ = true;
	collisionable_ = false;




	degats_ = 70;

	float x1 = x, y1 = y;

	setPosition({ x1,  y1 });

}