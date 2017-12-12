#include "AtkTest.h"

#include <iostream>

AtkTest::AtkTest()
{
	// TODO : Donner l'unité de temps en (milli)secondes

	cooldown_ = 100;
	t_ = 100;
	nom_ = "Attaque Test";
}


AtkTest::~AtkTest()
{
}

void AtkTest::utiliser(int x, int y)
{
	if (t_ >= cooldown_)
	{
		t_ = 0;
		debutX_ = x;
		debutY_ = y;
	}
}

void AtkTest::actualiser(std::vector<Projectile*> &projectiles)
{
	if (t_ < 20 && t_ % 5 == 0)
	{
		ProjTest *temp = new ProjTest(debutX_, debutY_);
		projectiles.push_back(temp);
	}
	
	if (t_ < cooldown_)
		t_++;
}
