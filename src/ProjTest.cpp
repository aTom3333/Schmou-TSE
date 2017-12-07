#include "ProjTest.h"

ProjTest::ProjTest()
{
	texture_.loadFromFile("../../rc/Sprites/base/projectile_test.png");
	sprite_.setTexture(texture_);
	position_.x = 0;
	position_.y = 0;
	age_ = 0;
	mx_ = my_ = 1;
}

ProjTest::~ProjTest()
{

}

void ProjTest::gestion(sf::RenderWindow &window)
{
	age_++;

	position_.x += 5*mx_;
	position_.y += 5*my_;

	if (position_.x > 800) mx_ = -1;
	if (position_.x < 0) mx_ = 1;
	if (position_.y > 600) my_ = -1;
	if (position_.y < 0) my_ = 1;

	afficher(window);
}

