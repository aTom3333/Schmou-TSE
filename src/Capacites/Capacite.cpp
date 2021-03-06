#include "Capacite.h"
#include "../Vaisseau/Vaisseau.h"

void Capacite::initIcon(size_t i)
{
	//TODO PG CONSTANTES MAGIQUES
	if (!tir_)
	{
		icone_.setPosition(900, 111 + i * 135);
		icone_.setColor({ 255,255,255 });
	}
	else
	{
		icone_.setPosition(20, 665 + i * 45);
		icone_.setColor({ 255,255,255 });
	}

	//Texte
	text_.setFont(*ecran_.getChargeur().getFont("hemi"));
	text_.setCharacterSize(25);
	text_.setFillColor({ 0, 0, 0, 102 });
	text_.setString(nom_);
	text_.setPosition(20 + 90 - text_.getGlobalBounds().width/2, 668 + i * 45);

    const sf::FloatRect rec = icone_.getGlobalBounds();//rectangle avec les dimensions du sprite icone_

	masque_.setSize({ rec.width, rec.height });
	masque_.setPosition(rec.left, rec.top);
	masque_.setFillColor({ 0,0,0, 172});

	t_lastuse_ = cooldown_;
}

void Capacite::gestionIcon()
{
    const sf::FloatRect rec = icone_.getGlobalBounds(); //rectangle avec les dimensions du sprite icone_
    const float ratio = t_lastuse_ >= cooldown_ ? 0 : 1.0f - t_lastuse_.asSeconds() / cooldown_.asSeconds();

	if (tir_)
	{
		masque_.setSize({ rec.width * ratio, rec.height });
		masque_.setPosition(icone_.getPosition().x + rec.width * (1.0f - ratio), icone_.getPosition().y);
	}
	else
	{
		masque_.setSize({ rec.width, ratio * rec.height });
	}
		

}
