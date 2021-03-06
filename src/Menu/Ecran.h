#ifndef CLASSE_ECRAN_H
#define CLASSE_ECRAN_H

#include "../constantes.h"
#include "../def_type.h"
#include "../Utilitaires/optional.h"
#include "../Utilitaires/Chargeur.h"
#include <memory>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using std::experimental::optional;
using std::experimental::make_optional;
using std::experimental::nullopt;

void chargement(sf::RenderWindow &window, sf::Texture &derniereFenetre);
void fade(sf::RenderWindow &window, sf::Texture &derniereFenetre);

class Ecran
{
	public:
		//structeurs
		explicit Ecran(sf::RenderWindow& window); /// < constructeur principal
		virtual ~Ecran() = default;

		virtual ecran_t executer(std::vector<std::unique_ptr<Ecran>> &vectEtats, sf::Texture &derniereFenetre) = 0;
		virtual optional<ecran_t> gestionEvent(const sf::Event& event);

		virtual std::unique_ptr<Ecran> factory() = 0;

		//getters
		bool isDetruit() const { return detruit_; }
		sf::Time getTempsFrame() const { return t_frame_; }
	
		sf::RenderWindow& getWindow() const { return window_; }
		Chargeur& getChargeur() { return chargeur_; }
		const sf::Clock& getClock() const { return horloge_; }
		vaisseau_container getVaisseauxContainer() const { return vaisseaux_; }
		void setVaisseau(vaisseau_ptr vaiss) { vaisseau_ = std::move(vaiss); }

		//setters
		virtual void setAfficheHUD(bool) {};

	protected:
		//Rendu
		sf::RenderWindow& window_; /// < Fenêtre de rendu SFML
		std::map<std::string, sf::Font> polices_ ; /// < map optionnelle de toutes les polices du jeu

		//Caractéristiques de code
		bool detruit_ = false;
		vaisseau_container vaisseaux_; ///vecteur des vaisseaux ennemis en jeu
		vaisseau_ptr vaisseau_; /// Vaisseau selectionné pour le hangar

		//Chargeur
		Chargeur chargeur_; /// < Chargeur associé

		//Temps
		sf::Clock horloge_; /// < Horloge globale de l'écran, réinitialisée à chaque affichage de window
		sf::Time t_frame_;///< Durée de la frame actuelle

};

#endif // !ECRAN_H
