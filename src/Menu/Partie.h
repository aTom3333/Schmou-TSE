#ifndef PARTIE_H
#define PARTIE_H

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "../Capacites/Capacite.h"
#include "../Projectiles/Projectile.h"
#include "../Vaisseau/Vaisseau.h"
#include "../Interface/Input.h"
#include "../Interface/Overlay.h"
#include "../Pattern/Vague.h"
#include "../def_type.h"
#include "Ecran.h"


/**
 * @class Partie
 * @brief Description brève
 *
 * Description détaillée
 */

// test

class Partie : public Ecran
{
	public:
		Partie(sf::RenderWindow& window, Input::Media media, bool afficheHUD = true, bool avecPattern = true);
		~Partie();

		void jeu();
		void collisionProjectile();
		void collisionVaisseaux();
		void deleteProjectileDetruit();
		void deleteVaisseauDetruit();

		void gestionFond(sf::Time &t);

		//Patterns
		void initPatternTest();

		ecran_t executer() override;
		std::unique_ptr<Ecran> factory() override;


	protected:
		//attributs de gameplay
		sf::Font font_; /// police principale
        Input input_; /// entrée
		Overlay hud_; /// Affichage Tête Haute

		std::vector<std::unique_ptr<sf::Texture>> fondTexture_;
		std::vector<sf::Sprite> fond_;

		std::vector<int> offset_;
			
		//pattern
		std::vector<Vague> pattern_;			

		//attributs principaux en jeu
		vaisseau_container vaisseaux_; ///vecteur des vaisseaux ennemis en jeu
		proj_container projectiles_; /// vecteur des projectiles en jeu

		//attributs de debug
		double timeSpeed_; /// Facteur contrôlant le temps
		bool avecPattern_;
		bool afficheHUD_; /// Vrai si on veux afficher le HUD, faux sinon

};

#endif // PARTIE_H