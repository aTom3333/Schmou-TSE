#include "Hangar.h"

Hangar::Hangar(sf::RenderWindow & window) : Ecran(window)
{
	fond_.setTexture(*chargeur_.getTexture("hangar.fond"));

	nom_.setFont(polices_["hemi"]);
	nom_.setFillColor({ 255, 255, 255 });
	nom_.setCharacterSize(68);
	nom_.setPosition(75, 40);

	for (size_t i = 0; i < NB_STATS; i++)
	{
		stats_[i].setFont(polices_["hemi"]);
		stats_[i].setFillColor({ 255, 255, 255 });
		stats_[i].setCharacterSize(20);
		stats_[i].setPosition(70, 230 + i*62);

		barres_[i].setFillColor({ 255, 255, 255, 100});
		barres_[i].setPosition(55, 243 + i * 62);
	}
}

ecran_t Hangar::executer(std::vector<std::unique_ptr<Ecran>>& vectEtats, sf::Texture & derniereFenetre)
{
	while (window_.isOpen())
	{
		sf::Event event;
		while (window_.pollEvent(event))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				detruit_ = false;
				derniereFenetre.update(window_);
				fade(window_, derniereFenetre);
				
				return PARTIE;
			}

			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Delete))
				return VIDE;
		}
		window_.clear();

		window_.draw(fond_);

		nom_.setString(vaisseau_->getNom());
		window_.draw(nom_);

		std::string temp[NB_STATS];
		temp[0] = std::to_string((int)vaisseau_->getPvMax()) + "(+" + std::to_string((int)vaisseau_->getPvRegen()) + "/sec)";
		temp[1] = std::to_string((int)vaisseau_->getArmureMax()) + "(+" + std::to_string((int)vaisseau_->getArmureRegen()) + "/sec)";
		temp[2] = std::to_string((int)vaisseau_->getBouclierMax()) + "(+" + std::to_string((int)vaisseau_->getBouclierRegen()) + "/sec)";
		temp[3] = std::to_string((int)vaisseau_->getatqM());
		temp[4] = std::to_string((int)vaisseau_->getVitMax());

		float ratio[NB_STATS];
		ratio[0] = vaisseau_->getPvMax() > MAX_PV ? 1.f : vaisseau_->getPvMax() / MAX_PV;
		ratio[1] = vaisseau_->getArmureMax() > MAX_ARMURE ? 1.f : vaisseau_->getArmureMax() / MAX_ARMURE;
		ratio[2] = vaisseau_->getBouclierMax() > MAX_BOUCLIER ? 1.f : vaisseau_->getBouclierMax() / MAX_BOUCLIER;
		ratio[3] = vaisseau_->getatqM() > MAX_ATK ? 1.f : vaisseau_->getatqM() / MAX_ATK;
		ratio[4] = vaisseau_->getVitMax() > MAX_VITESSE ? 1.f : vaisseau_->getVitMax() / MAX_VITESSE;

		
		for (size_t i = 0; i < NB_STATS; i++)
		{
			stats_[i].setString(temp[i]);
			window_.draw(stats_[i]);

			barres_[i].setSize({ ratio[i] * BARRE_STATS_W, BARRE_STATS_H });
			window_.draw(barres_[i]);
		}

		window_.display();
	}

	return PARTIE;
}

std::unique_ptr<Ecran> Hangar::factory()
{
	return std::unique_ptr<Ecran>(new Hangar(window_));
}
