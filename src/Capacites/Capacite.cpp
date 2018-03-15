#include <vector>
#include <string>
#include <algorithm>
#include "Capacite.h"
#include "../Vaisseau/Vaisseau.h"
#include "../Projectiles/Projectile.h"

void Capacite::initIcon(int i)
{
	if (!tir_)
	{
		capacite_.setPosition(900, 111 + i * 135);
		capacite_.setColor({ 255,255,255 });
	}
	else
	{
		capacite_.setPosition(20, 665 + i * 45);
		capacite_.setColor({ 255,255,255 });
	}

	font_.loadFromFile("../../rc/Font/hemi.ttf");
	text_.setFont(font_);
	text_.setCharacterSize(25);
	text_.setFillColor({ 0, 0, 0, 102 });
	text_.setString(nom_);
	text_.setPosition(20 + 90 - text_.getGlobalBounds().width/2, 668 + i * 45);

	sf::FloatRect rec = capacite_.getGlobalBounds();

	masque_.setSize({ rec.width, rec.height });
	masque_.setPosition(rec.left, rec.top);
	masque_.setFillColor({ 0,0,0, 172});
}

void Capacite::gestionIcon()
{
	sf::FloatRect rec = capacite_.getGlobalBounds();
	float ratio = t_ >= cooldown_ ? 0 : 1 - t_ / cooldown_;

	if (tir_)
	{
		masque_.setSize({ rec.width * ratio, rec.height });
		masque_.setPosition(capacite_.getPosition().x + rec.width * (1 - ratio), capacite_.getPosition().y);
	}
	else
	{
		masque_.setSize({ rec.width, ratio * rec.height });
	}
		

}
