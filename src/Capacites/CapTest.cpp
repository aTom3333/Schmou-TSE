#include "CapTest.h"
#include "CapDash.h"

CapTest::CapTest()
{
	// TODO : Donner l'unit� de temps en (milli)secondes

	cooldown_ = 100;
	t_ = cooldown_;
	nom_ = "Attaque Test";
}


CapTest::~CapTest()
{
}

void CapTest::utiliser(int x, int y)
{
	// Si la comp�tence est disponible
	if (t_ >= cooldown_)
	{
		// D�but du timer
		t_ = 0;
		// Initialisation de l'endroit ou la comp�tence � �t� utilis�e
		debutX_ = x;
		debutY_ = y;
	}
}

void CapTest::actualiser(std::vector<Projectile*>& projectiles, Entite * vaisseau)
{
	// Pour avoir la cr�ation des 4 projectile toute les 5 frames
	if (t_ < 20 && t_ % 5 == 0)
	{
		// Cr�ation d'un nouveau projectile
		ProjTest *temp = new ProjTest(debutX_, debutY_);
		projectiles.push_back(temp);
	}

	// Si la comp�tance est en cooldown, on actualise le timer
	if (t_ < cooldown_)
		t_++;
}
