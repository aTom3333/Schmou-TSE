#include "Overlay.h"

Overlay::Overlay()
{
	font_.loadFromFile("../../rc/Font/hemi.ttf");
	overlayText_.loadFromFile("../../rc/UI/overlay.png");
	overlay_.setTexture(overlayText_);

	for (int i = 0; i < 3; i++)
	{
		barre_[i].setSize({ OVERLAY_BARRE_W, OVERLAY_BARRE_H });
		barre_[i].setPosition(5, 7 + (OVERLAY_BARRE_H + 4) * i);
		barre_[i].setFillColor({ 255, 255, 255, 102 });
	}

	for (int i = 0; i < 4; i++)
	{
		statuts_[i].setFont(font_);
		statuts_[i].setCharacterSize(20);
		statuts_[i].setFillColor({ 255, 255, 255, 102 });
		statuts_[i].setPosition(164, 108 + 25 * i);
	}
}

Overlay::~Overlay()
{
}

void Overlay::draw(sf::RenderWindow & window, bool bDraw)
{
	if (bDraw)
	{
		window.draw(overlay_);
		for(int i = 0; i < 3; i++)
			window.draw(barre_[i]);
		for (int i = 0; i < 4; i++)
			window.draw(statuts_[i]);
	}
}

void Overlay::gestion(Entite * vaisseau)
{
	barre_[0].setSize({ OVERLAY_BARRE_W*vaisseau->getPV() / vaisseau->getPVMax(), OVERLAY_BARRE_H });
	barre_[1].setSize({ OVERLAY_BARRE_W*vaisseau->getArmure() / vaisseau->getArmureMax(), OVERLAY_BARRE_H });
	barre_[2].setSize({ OVERLAY_BARRE_W*vaisseau->getBouclier() / vaisseau->getBouclierMax(), OVERLAY_BARRE_H });

	statuts_[0].setString("Statuts : ok");
	statuts_[1].setString("Coque : " + std::to_string((int)(vaisseau->getPV() / vaisseau->getPVMax() * 100))+"%");
	statuts_[2].setString("Armure : " + std::to_string((int)(vaisseau->getArmure() / vaisseau->getArmureMax() * 100))+"%");
	statuts_[3].setString("Bouclier : " + std::to_string((int)(vaisseau->getBouclier() / vaisseau->getBouclierMax() * 100))+"%");
}
