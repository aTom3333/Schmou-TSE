#include "CapPiou.h"

CapPiou::CapPiou()
{
	// TODO : Donner l'unité de temps en (milli)secondes

	cooldown_ = 20;
	t_ = cooldown_;
	nom_ = "Attaque Piou";
}


CapPiou::~CapPiou()
{
}

void CapPiou::utiliser(int x, int y)
{
	if (t_ >= cooldown_)
	{
		t_ = 0;
		debutX_ = x;
		debutY_ = y;
	}
}

void CapPiou::actualiser(std::vector<Projectile*> &projectiles)
{
	if (t_ == 0)
	{
		ProjPiou *temp = new ProjPiou(debutX_, debutY_);
		projectiles.push_back(temp);
	}

	if (t_ < cooldown_)
		t_++;
}
