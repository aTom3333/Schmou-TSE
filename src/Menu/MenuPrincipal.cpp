#include "MenuPrincipal.h"

MenuPrincipal::MenuPrincipal(sf::RenderWindow & window) : Ecran(window)
{
	fondText_.loadFromFile("../../rc/Accueil/menu_principal.png");
	fond_.setTexture(fondText_);

	version_.setFont(polices_["hemi"]);
	version_.setCharacterSize(21);
	version_.setString("Version " VERSION " " BRANCHE);
	version_.setPosition(0, ECRAN_H - version_.getGlobalBounds().height - 4);

	sf::Text temp;
	temp.setFont(polices_["hemi"]);
	temp.setCharacterSize(50);
	
	temp.setString("Nouvelle Partie");
	textes_.push_back(temp);
	temp.setString("Continuer");
	textes_.push_back(temp);
	temp.setString("Options");
	textes_.push_back(temp);
	temp.setString("Quitter");
	textes_.push_back(temp);

	for (size_t i = 0; i < textes_.size(); i++)
		textes_[i].setPosition(100, 310 + 60*i);
}

ecran_t MenuPrincipal::executer(std::vector<std::unique_ptr<Ecran>>& vectEtats, sf::Texture & derniereFenetre)
{
	selection_ = -1;

	while (window_.isOpen())
	{
		// Gestion  des évènements 
		sf::Event event;
		while (window_.pollEvent(event))
		{
			auto retour = gestionEvent(event);
			if(retour) {
				if(retour == PARTIE)
					derniereFenetre.update(window_);
				return *retour;
			}
		}

		// Efface l'écran
		window_.clear();

		window_.draw(fond_);
		window_.draw(version_);
			

		for (size_t i = 0; i < textes_.size(); i++)
		{
			if (i == selection_)
				textes_[i].setPosition(200, 310 + 60 * i);
			else
				textes_[i].setPosition(100, 310 + 60 * i);

			window_.draw(textes_[i]);
		}
			

		// Mise à jour de l'écran
		window_.display();
	}

	return ACCUEIL;
}

std::unique_ptr<Ecran> MenuPrincipal::factory()
{
	return std::unique_ptr<Ecran>(std::make_unique<MenuPrincipal>(window_));
}

optional<ecran_t> MenuPrincipal::gestionEvent(const sf::Event& event)
{
	auto retour = Ecran::gestionEvent(event);
	if(retour)
		return retour;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		return make_optional(ACCUEIL);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if(selection_ <= 0)
			selection_ = 3;
		else
			selection_--;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (selection_ >= 3)
			selection_ = 0;
		else
			selection_++;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		switch (selection_)
		{
			case 0:
				return make_optional(PARTIE);
			case 1:
				break;
			case 2:
				break;
			case 3:
				return make_optional(VIDE);
			default:
				break;

		}
	}
	
	return nullopt;
}
