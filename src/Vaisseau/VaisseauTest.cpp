#include "VaisseauTest.h"


VaisseauTest::VaisseauTest() ///constructeur
{
	//sprite
	texture_.loadFromFile("../../rc/Sprites/base/vaisseau.png");
	sprite_.setTexture(texture_);

	//hitbox simple
	cercleEnglobant_ = sf::CircleShape(64);
	cercleEnglobant_.setOrigin(64, 64);

	vit_ = 500;

}

VaisseauTest::~VaisseauTest()///destructeur
{
}

void VaisseauTest::gestion(sf::RenderWindow & window, float tempsEcoule)
{
	afficher(window);
}

