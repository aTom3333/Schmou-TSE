#ifndef PROJ_TEST_H
#define PROJ_TEST_H

#include "Projectile.h"

/**
* @class ProjTest
* @brief Projectile de test
*
* Lance 4 boules qui rebondissent sur les bord de l'écran
*/

class ProjTest : public Projectile
{
	public:
		ProjTest(); 
		ProjTest(int x, int y); 
		~ProjTest(); 
		void gestion(sf::RenderWindow &window);
	private:
		int mx_; /// Multiplicateur (1 ou -1) pour gérer le sens du projectile
		int my_; /// Multiplicateur (1 ou -1) pour gérer le sens du projectile
		int vx_; /// Vitesse horizontale
		int vy_; /// Vitesse Verticale
};

#endif //PROJ_TEST_H