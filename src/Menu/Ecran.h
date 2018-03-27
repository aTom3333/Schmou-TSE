#ifndef CLASSE_ECRAN_H
#define CLASSE_ECRAN_H

#include "../constantes.h"
#include "../Utilitaires/optional.h"
#include "../Utilitaires/Chargeur.h"

#include <stack>
#include <memory>
#include <vector>
#include <map>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

void chargement(sf::RenderWindow &window, sf::Texture &derniereFenetre);

class Ecran
{
	public:
		//structeurs
		Ecran(sf::RenderWindow& window); /// < constructeur principal
		virtual ~Ecran() = default;

		virtual ecran_t executer(sf::Texture &derniereFenetre) = 0;

		virtual std::unique_ptr<Ecran> factory() = 0;

		//getters
		bool isDetruit() const { return detruit_; }
	
		sf::RenderWindow& getWindow() { return window_; }
		Chargeur& getChargeur() { return chargeur_; }
		const sf::Clock& getClock() const { return horloge_; }

	protected:
		sf::RenderWindow& window_; /// < Fenêtre de rendu SFML
		std::map<std::string, sf::Font> polices_ ; /// < map optionnelle de toutes les polices du jeu
		bool detruit_ = false;
		Chargeur chargeur_;
		sf::Clock horloge_; /// < horloge globale de l'écran, réinitialisée à chaque affichage de window

};

#endif // !ECRAN_H
