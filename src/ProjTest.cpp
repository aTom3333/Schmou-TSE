#include "ProjTest.h"


ProjTest::ProjTest()
{
	texture_.loadFromFile("../../rc/Sprites/base/projectile_test.png");
	sprite_.setTexture(texture_);
	position_.x = 0;
	position_.y = 0;
	age_ = 0;
}

ProjTest::~ProjTest()
{

}

void ProjTest::gestion(sf::RenderWindow &window)
{
	age_++;

	position_.x = age_;
	position_.y = age_;
	
	
	afficher(window);
}

