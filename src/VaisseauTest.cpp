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

void VaisseauTest::gestion(sf::RenderWindow & window)
{
	bool zqsd = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		position_.x -= (float)vit_ / 100.;
		zqsd = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		position_.x += (float)vit_ / 100.;
		zqsd = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		position_.y -= (float)vit_ / 100.;
		zqsd = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		position_.y += (float)vit_ / 100.;
		zqsd = true;
	}
	
	if (!zqsd)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			position_.x -= (float)vit_ / 100.;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			position_.x += (float)vit_ / 100.;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			position_.y -= (float)vit_ / 100.;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			position_.y += (float)vit_ / 100.;
		}
	}
	



	afficher(window);
}

