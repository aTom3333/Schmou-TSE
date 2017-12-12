#include "VaisseauTest.h"


VaisseauTest::VaisseauTest() ///constructeur
{
	//sprite
	texture_.loadFromFile("../../rc/Sprites/base/vaisseau.png");
	sprite_.setTexture(texture_);

	//hitbox simple
	cercleEnglobant_ = sf::CircleShape(64);
	cercleEnglobant_.setOrigin(64, 64);


}

VaisseauTest::~VaisseauTest()///destructeur
{
}

void VaisseauTest::gestion(sf::RenderWindow & window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		position_.x -= vit_ / 100;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		position_.x += vit_ / 100;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		position_.y += vit_ / 100;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		position_.y -= vit_ / 100; 
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		position_.x -= vit_ / 100;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		position_.x += vit_ / 100;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		position_.y += vit_ / 100; 
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		position_.y -= vit_ / 100;
	}



	afficher(window);
}

