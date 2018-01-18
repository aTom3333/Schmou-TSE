#include "CapMissile.h"

CapMissile::CapMissile()
{
	cooldown_ = 5000;
	t_ = cooldown_;
	frames_ = cooldown_;
	nom_ = "Missile";
}

void CapMissile::utiliser(int x, int y)
{
	// Si la comp�tence est disponible
	if (t_ >= cooldown_)
	{
		// D�but du timer
		t_ = 0;
		frames_ = 0;
		// Initialisation de l'endroit ou la comp�tence a �t� utilis�e
		debutX_ = x;
		debutY_ = y;
	}
}

void CapMissile::actualiser(std::vector<Projectile*>& projectiles, Entite & vaisseau, float tempsEcoule)
{
	// Cr�ation du projectile au moment o� la comp�tence est lanc�e
	if (frames_ == 0)
	{
		ProjMissile *temp = new ProjMissile(debutX_, debutY_);
		projectiles.push_back(temp);
	}

	// Si la comp�tence est en cooldown, on actualise le timer
	if (t_ < cooldown_)
	{
		t_ += tempsEcoule;
	}
	frames_++;
}