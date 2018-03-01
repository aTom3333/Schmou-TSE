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
		Partie(sf::RenderWindow& window);
		~Partie();

		void jeu();
		void collisionProjectile();
		void collisionVaisseaux();
		void deleteProjectileDetruit();
		void deleteVaisseauDetruit();

		//TODO temporaire pour tester, n'existe pas dans le jeu livré
		void testProjTest();
		void testVaisseauTest();

	private:
		//attributs de gameplay
        sf::RenderWindow& window_; /// fenêtre principale
		sf::Font font_; /// police principale
        Input input_; /// entrée
		Overlay hud_; /// Affichage Tête Haute
		bool afficheHUD_; /// Vrai si on veux afficher le HUD, faux sinon

		//attributs principaux en jeu
		std::vector<Vaisseau*> vaisseaux_; ///vecteur des vaisseaux ennemis en jeu
		std::vector<Projectile *> projectiles_; /// vecteur des projectiles en jeu

		//attributs de debug
		float timeSpeed_; /// Facteur controllant le temps

};

#endif // PARTIE_H
