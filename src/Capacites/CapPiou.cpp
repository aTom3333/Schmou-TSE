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

void CapPiou::actualiser(std::vector<Projectile*> &projectiles, Entite *vaisseau)
{
	// Création du projectile au moment où la compétance est lancée
	if (t_ == 0)
	{
		ProjPiou *temp = new ProjPiou(debutX_, debutY_);
		projectiles.push_back(temp);
	}

	// Si la compétance est en cooldown, on actualise le timer
	if (t_ < cooldown_)
		t_++;
}
