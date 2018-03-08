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
		capacite_.setColor({ 255,255,255, 102 });
	}

	font_.loadFromFile("../../rc/Font/hemi.ttf");
	text_.setFont(font_);
	text_.setCharacterSize(25);
	text_.setFillColor({ 0, 0, 0, 102 });
	text_.setString(nom_);
	text_.setPosition(20 + 90 - text_.getGlobalBounds().width/2, 668 + i * 45);
	
}
