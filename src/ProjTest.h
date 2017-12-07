#ifndef PROJ_TEST_H
#define PROJ_TEST_H

#include "Projectile.h"


class ProjTest : public Projectile
{
	public:
		ProjTest();
		void gestion(sf::RenderWindow &window);
	private:
		int mx_;
		int my_;
		int vx_, vy_;
};

#endif