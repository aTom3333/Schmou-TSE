#ifndef CLASSE_ECRAN_H
#define CLASSE_ECRAN_H

#include "../constantes.h"
#include "../Utilitaires/optional.h"

#include <stack>
#include <memory>
#include <vector>
#include <map>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class Ecran
{
	public:
		//structeurs
		Ecran(sf::RenderWindow& window); /// < constructeur principal
		virtual ~Ecran() = default;

		virtual ecran_t executer() = 0;

		virtual std::unique_ptr<Ecran> factory() = 0;

		//getters
		bool isDetruit() const { return detruit_; }

	protected:
		sf::RenderWindow& window_;
		static std::experimental::optional < std::map < std::string, sf::Font >> polices_ ; /// < map optionnelle de toutes les polices du jeu
		bool detruit_ = false;

};

#endif // !ECRAN_H
