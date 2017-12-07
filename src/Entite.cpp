#include "Entite.h"
#include "Collision.h"


bool collision(const Entite& e1, const Entite& e2)
{
	if(!e1.collisionable_ || !e2.collisionable_)
		return false;
	/*if(e1.joueur_ == e2.joueur_)
		return false;*/
	return collision(e1.cercleEnglobant_, e2.cercleEnglobant_);
	// TODO Tester avec la forme complète
}
#include "Entite.h"

void Entite::afficher(sf::RenderWindow &window)
{
	window.draw(sprite_);
}

void Entite::setPosition(const sf::Vector2f & pos)
{
	position_ = pos;
	sprite_.setPosition(position_);
	cercleEnglobant_.setPosition(pos);
	for (auto f : forme_)
		f->setPosition(pos);
}
