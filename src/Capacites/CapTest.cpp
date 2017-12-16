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
	// Si la compétence est disponible
	if (t_ >= cooldown_)
	{
		// Début du timer
		t_ = 0;
		// Initialisation de l'endroit ou la compétence à été utilisée
		debutX_ = x;
		debutY_ = y;
	}
}

void CapTest::actualiser(std::vector<Projectile*>& projectiles, Entite * vaisseau)
{
	// Pour avoir la création des 4 projectile toute les 5 frames
	if (t_ < 20 && t_ % 5 == 0)
	{
		// Création d'un nouveau projectile
		ProjTest *temp = new ProjTest(debutX_, debutY_);
		projectiles.push_back(temp);
	}

	// Si la compétance est en cooldown, on actualise le timer
	if (t_ < cooldown_)
		t_++;
}
