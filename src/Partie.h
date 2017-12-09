#ifndef PARTIE_H
#define PARTIE_H

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Capacite.h"
#include "Projectile.h"
#include "Vaisseau.h"


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
		Partie();
		~Partie();

		void jeu(sf::RenderWindow &window);
		void Partie::testCollision(std::vector<Projectile*> &projectiles);

	private:
		sf::Font font_;

};

#endif // PARTIE_H
