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
		void testCollision(std::vector<Projectile*> &projectiles);

		//TODO temporaire pour tester, n'existe pas dans le jeu livré
		void testProjTest();
		void testVaisseauTest();

	private:
		//attributs de gameplay
        sf::RenderWindow& window_; /// fenêtre principale
		sf::Font font_; /// police principale
        Input input_; /// entrée

		//attributs principaux en jeu
		std::vector<Vaisseau*> vaisseaux_; ///vecteur des vaisseaux ennemis en jeu
		std::vector<Capacite*> capacites_; ///TODO temporaire : vectuer des capacités à mettre dans la classe Vaisseau
		std::vector<Projectile *> projectiles_; /// vecteur des projectiles en jeu

};

#endif // PARTIE_H
