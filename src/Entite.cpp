#include "Entite.h"
#include "Utilitaires/Collision.h"
#include "constantes.h"
#include <cmath>


bool collision(const Entite& e1, const Entite& e2)
{
	if(!e1.collisionable_ || !e2.collisionable_)
		return false;
//	if(e1.equipe_ == e2.equipe_)
//		return false;
	if(!collision(e1.cercleEnglobant_, e2.cercleEnglobant_))
		return false;
	for(const auto& f1 : e1.forme_)
		for(const auto& f2 : e2.forme_)
			if(collision(*f1, *f2))
				return true;
	return false;
}

void Entite::afficher(sf::RenderWindow & window, bool debug) const
{
	window.draw(sprite_);

	if(debug)
	{
		window.draw(cercleEnglobant_);
		for(auto& elem: forme_)
			window.draw(*elem);
	}
}


void Entite::move(const sf::Vector2f& delta)
{
	for(auto& elem : forme_)
		elem->move(delta);
    cercleEnglobant_.move(delta);
    sprite_.move(delta);
	position_ += delta;
}

void Entite::setPosition(const sf::Vector2f & pos)
{
	move(pos - position_);
}


const sf::Vector2f& Entite::getPosition() const
{
	return position_;
}

void Entite::rotate(float angle)
{
	for(auto& elem : forme_)
		elem->rotate(angle);
    cercleEnglobant_.rotate(angle);
    sprite_.rotate(angle);
	angle_ = fmod(angle_ + angle, 360);
}

void Entite::setRotation(float angle)
{
	rotate(angle - angle_);
}

float Entite::getRotation() const
{
	return angle_;
}

void Entite::scale(float factor)
{
	for(auto& elem : forme_)
		elem->scale(factor, factor);
    cercleEnglobant_.scale(factor, factor);
    sprite_.scale(factor, factor);
	scale_ *= factor;
}

void Entite::setScale(float factor)
{
	scale(factor / scale_);
}

float Entite::getScale() const
{
	return scale_;
}

void Entite::changeSpeed(int val)
{
	vit_ += val;
}

void Entite::setDetruit(bool val)
{
	detruit_ = val;
}

bool Entite::estDetruit() const
{
	return detruit_;
}

bool Entite::estDehors(float x_min, float y_min, float x_max, float y_max) const
{
    float R = cercleEnglobant_.getRadius();
    return position_.x < x_min - R || position_.x > x_max + R || position_.y < y_min - R || position_.y > y_max + R;
}

bool Entite::estDedans(float x_min, float y_min, float x_max, float y_max) const
{
    float R = cercleEnglobant_.getRadius();
    return position_.x > x_min + R && position_.x < x_max - R && position_.y > y_min + R && position_.y < y_max - R;
}
