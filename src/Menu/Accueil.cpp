#include "Accueil.h"

Accueil::Accueil(sf::RenderWindow & window) : Ecran(window) 
{
	fondText_.loadFromFile("../../rc/Accueil/titre.png");
	fond_.setTexture(fondText_);

	texte_.setFont(polices_["hemi"]);
	texte_.setString("Appuyez sur Entrée");
	texte_.setCharacterSize(32);
	texte_.setPosition(ECRAN_L / 2 - texte_.getGlobalBounds().width / 2, 682);
}

ecran_t Accueil::executer(sf::Texture &derniereFenetre)
{
	sf::Clock timer;
	int alpha = 255;
	int mult = -1;

	auto t = timer.restart();
	while (window_.isOpen())
	{
		// Gestion  des évènements 
		sf::Event event;
		while (window_.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Delete))
				//TODO PG 07-03-2018 j'ai mis Suppr pour fermer temporairement
				window_.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				derniereFenetre.update(window_);
				return MENU_PRINCIPAL;
			}
		}

		// Efface l'écran
		window_.clear();

		t = timer.getElapsedTime();
		if (t.asMilliseconds() > 50)
		{
			alpha += mult*10;

			if (alpha < 0)
			{
				alpha = 0;
				mult = -mult;
			}
			if (alpha > 255)
			{
				alpha = 255;
				mult = -mult;
			}

			texte_.setFillColor({ 255, 255, 255, (sf::Uint8)alpha });
			t = timer.restart();
		}

		window_.draw(fond_);
		window_.draw(texte_);

		// Mise à jour de l'écran
		window_.display();
	}

	return VIDE;
}

std::unique_ptr<Ecran> Accueil::factory()
{
	return std::unique_ptr<Ecran>(new Accueil(window_));
}
