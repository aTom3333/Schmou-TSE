#include "Accueil.h"

ecran_t Accueil::executer()
{
	while (window_.isOpen())
	{
		// Gestion  des �v�nements 
		sf::Event event;
		while (window_.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Delete))
				//TODO PG 07-03-2018 j'ai mis Suppr pour fermer temporairement
				window_.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				return PARTIE;
			}
		}


		// Efface l'�cran
		window_.clear();

		// Mise � jour de l'�cran
		window_.display();
	}

	return VIDE;
}

std::unique_ptr<Ecran> Accueil::factory()
{
	return std::unique_ptr<Ecran>(new Accueil(window_));
}
