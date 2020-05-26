#include "Module.h"
#include <cmath>


float distance(sf::Vector2f p1, sf::Vector2f p2) {
    return std::hypot(p1.x - p2.x, p1.y - p2.y);
}

Module::Module(Ecran& ecran, module_t type, float x, float y) : ecran_{ecran}, type_{type}, x_{x}, y_{y} {
    switch (type_)
	{
		case ATTAQUE:
			nom_ = "Vide (Attaque)";
			sprite_.setTexture(*ecran_.getChargeur().getTexture("hangar.icone.atk"));
			break;
		case DEFENSE:
			nom_ = "Vide (Défense)";
			sprite_.setTexture(*ecran_.getChargeur().getTexture("hangar.icone.def"));
			break;
		case UTILITAIRE :
			nom_ = "Vide (Utilitaire)";
			sprite_.setTexture(*ecran_.getChargeur().getTexture("hangar.icone.div"));
			break;
		case DEPLACEMENT:
			nom_ = "Vide (Déplacement)";
			sprite_.setTexture(*ecran_.getChargeur().getTexture("hangar.icone.dep"));
			break;
		default:
			break;
	}
}

void Module::init(size_t id)
{
	id_ = id;
	switch (id_)
	{
		case 0:
			break;
		default:
			break;
	}
}

void Module::checkSelection(sf::Vector2f curseur, sf::Vector2f& res, float offsetX, float offsetY)
{
	if (res.x == 0 && res.y == 0)
	{
		sf::Vector2f pos = { (x_ + sprite_.getGlobalBounds().width/2.f + offsetX), (y_ + sprite_.getGlobalBounds().height/2.f + offsetY) };
		res = distance(curseur, pos) < std::max(sprite_.getGlobalBounds().width/2, sprite_.getGlobalBounds().height/2) ? 
			sf::Vector2f(pos.x - sprite_.getGlobalBounds().width / 2.f - 8, pos.y- sprite_.getGlobalBounds().height / 2.f - 11)
	   		: sf::Vector2f(0, 0);
	}
}

int Module::checkPosition(float size)
{
	return x_ < size/2.f ? -1 : 1;
}

void Module::setPositionModules(float x, float y)
{
	sprite_.setPosition(x + x_, y + y_);
}
