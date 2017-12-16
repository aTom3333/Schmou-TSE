#include "CapPiou.h"

CapPiou::CapPiou()
{
	// TODO : Donner l'unit� de temps en (milli)secondes

	cooldown_ = 20;
	t_ = cooldown_;
	nom_ = "Attaque Piou";
}


CapPiou::~CapPiou()
{
}

void CapPiou::utiliser(int x, int y)
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

void CapPiou::actualiser(std::vector<Projectile*> &projectiles, Entite *vaisseau)
{
	// Cr�ation du projectile au moment o� la comp�tance est lanc�e
	if (t_ == 0)
	{
		ProjPiou *temp = new ProjPiou(debutX_, debutY_);
		projectiles.push_back(temp);
	}

	// Si la comp�tance est en cooldown, on actualise le timer
	if (t_ < cooldown_)
		t_++;
}
