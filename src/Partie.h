#ifndef PARTIE_H
#define PARTIE_H

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Capacites/Capacite.h"
#include "Projectiles/Projectile.h"
#include "Vaisseau/Vaisseau.h"
#include "Interface/Input.h"
#include "Interface/Overlay.h"
#include "Pattern\Vague.h"


/**
 * @class Partie
 * @brief Description brève
 *
 * Description détaillée
 */

// test

class Partie
{
	public:
		Partie(sf::RenderWindow& window, Input::Media media, bool afficheHUD = true, bool avecVagues = true);
		~Partie();

		void jeu();
		void collisionProjectile();
		void collisionVaisseaux();
		void deleteProjectileDetruit();
		void deleteVaisseauDetruit();

		//Patterns
		void initPatternTest();

		//TODO temporaire pour tester, n'existe pas dans le jeu livré
		void testPartie();

	protected:
		//attributs de gameplay
        sf::RenderWindow& window_; /// fenêtre principale
		sf::Font font_; /// police principale
        Input input_; /// entrée
		Overlay hud_; /// Affichage Tête Haute
			
		//pattern
		std::vector<Vague> pattern_;			

		//attributs principaux en jeu
		std::vector<Vaisseau*> vaisseaux_; ///vecteur des vaisseaux ennemis en jeu
		std::vector<Projectile *> projectiles_; /// vecteur des projectiles en jeu

		//attributs de debug
		double timeSpeed_; /// Facteur contrôlant le temps
		bool avecPattern_;
		bool afficheHUD_; /// Vrai si on veux afficher le HUD, faux sinon

};

#endif // PARTIE_H
