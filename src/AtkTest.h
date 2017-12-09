#ifndef ATKTEST_H
#define ATKTEST_H

#include "Attaque.h"
#include "Projectile.h"
#include "ProjTest.h"

class AtkTest : public Attaque
{
	public:
		AtkTest();
		~AtkTest();
		void utiliser(int x, int y);
		void actualiser(std::vector<Projectile*> &projectiles);
};

#endif
