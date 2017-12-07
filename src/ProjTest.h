#ifndef PROJ_TEST_H
#define PROJ_TEST_H

#include "Projectile.h"


class ProjTest : public Projectile
{
	public:
		ProjTest();
		~ProjTest();
		void gestion(sf::RenderWindow &window);
	private:

};

#endif