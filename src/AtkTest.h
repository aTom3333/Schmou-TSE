#ifndef ATKTEST_H
#define ATKTEST_H

#include "Capacite.h"
#include "Projectile.h"
#include "ProjTest.h"

class AtkTest : public Capacite
{
	public:
		AtkTest();
		~AtkTest();
		void utiliser(int x, int y);
		void actualiser(std::vector<Projectile*> &projectiles);
};

#endif
