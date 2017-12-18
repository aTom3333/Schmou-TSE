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
        sf::RenderWindow& window_;
		sf::Font font_;
        Input input_;
};

#endif // PARTIE_H
