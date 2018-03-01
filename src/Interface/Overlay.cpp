#include "Overlay.h"

Overlay::Overlay()
{
}

void Overlay::init(Vaisseau *vaisseau)
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

	int n = 0;

	for (int i = 0; i < vaisseau->getskills().size(); i++)
	{
		vaisseau->getskills()[i]->initIcon(n);
		n += vaisseau->getskills()[i]->getAffiche() ? 1 : 0;
	}

	statuts_ = new sf::Text[n];
	for (int i = 0; i < n; i++)
	{
		statuts_[i].setFont(font_);
		statuts_[i].setCharacterSize(20);
		statuts_[i].setFillColor({ 0, 0, 0, 102 });
		statuts_[i].setPosition(935, 185 + 135 * i);
	}
}

Overlay::~Overlay()
{
	delete[] statuts_;
}

void Overlay::draw(sf::RenderWindow & window, Vaisseau * vaisseau, bool bDraw)
{
	if (bDraw)
	{
		window.draw(overlay_);
		for(int i = 0; i < 3; i++)
			window.draw(barre_[i]);

		int n = 0;
		for (int i = 0; i < vaisseau->getskills().size(); i++)
		{
			if (vaisseau->getskills()[i]->getAffiche())
			{
				window.draw(vaisseau->getskills()[i]->getIcon());
				window.draw(statuts_[n]);
				n++;
			}
			
		}
			
	}
}

void Overlay::gestion(Vaisseau * vaisseau)
{
	barre_[0].setSize({ OVERLAY_BARRE_W*vaisseau->getPV() / vaisseau->getPVMax(), OVERLAY_BARRE_H });
	barre_[1].setSize({ OVERLAY_BARRE_W*vaisseau->getArmure() / vaisseau->getArmureMax(), OVERLAY_BARRE_H });
	barre_[2].setSize({ OVERLAY_BARRE_W*vaisseau->getBouclier() / vaisseau->getBouclierMax(), OVERLAY_BARRE_H });


	int n = 0;
	for (int i = 0; i < vaisseau->getskills().size(); i++)
	{
		if (vaisseau->getskills()[i]->getAffiche())
		{
			int cooldown = (int)(vaisseau->getskills()[i]->getCooldown() - vaisseau->getskills()[i]->getTime());
			std::string str = cooldown <= 0 ? "Ready" : std::to_string(cooldown);
			statuts_[n].setString(str);

			statuts_[n].setPosition(1015 - statuts_[n].getLocalBounds().width, statuts_[n].getPosition().y);
			n++;
		}
	}
		
}
