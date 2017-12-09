#ifndef PROJ_TEST_H
#define PROJ_TEST_H

#include "Projectile.h"


class ProjTest : public Projectile
{
	public:
		ProjTest();
		ProjTest(int x, int y);
		~ProjTest();
		void gestion(sf::RenderWindow &window);
	private:
		int mx_;/// 
		int my_;/// 
		int vx_;/// 
		int vy_;/// 
};

#endif //PROJ_TEST_H