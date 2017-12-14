#include "CapTest.h"
#include "CapDash.h"

CapTest::CapTest()
{
	// TODO : Donner l'unité de temps en (milli)secondes

	cooldown_ = 100;
	t_ = cooldown_;
	nom_ = "Attaque Test";
}


CapTest::~CapTest()
{
}

void CapTest::utiliser(int x, int y)
{
	if (t_ >= cooldown_)
	{
		t_ = 0;
		debutX_ = x;
		debutY_ = y;
	}
}

void CapTest::actualiser(std::vector<Projectile*>& projectiles, Entite * vaisseau)
{
	if (t_ < 20 && t_ % 5 == 0)
	{
		ProjTest *temp = new ProjTest(debutX_, debutY_);
		projectiles.push_back(temp);
	}

	if (t_ < cooldown_)
		t_++;
}
