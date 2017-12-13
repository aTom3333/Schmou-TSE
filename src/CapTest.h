#ifndef CAPTEST_H
#define CAPTEST_H

#include "Capacite.h"
#include "Projectile.h"
#include "ProjTest.h"

class CapTest : public Capacite
{
	public:
		CapTest();
		~CapTest();
		void utiliser(int x, int y);
		void actualiser(std::vector<Projectile*> &projectiles);
};

#endif
