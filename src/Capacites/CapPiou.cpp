#include "CapPiou.h"

CapPiou::CapPiou()
{
	cooldown_ = 100;
	t_ = cooldown_;
	frames_ = cooldown_;
	nom_ = "Attaque Piou";
}


void CapPiou::utiliser(int x, int y)
{
	// Si la compétence est disponible
	if (t_ >= cooldown_)
	{
		// Début du timer
		t_ = 0;
		frames_ = 0;
		// Initialisation de l'endroit ou la compétence a été utilisée
		debutX_ = x;
		debutY_ = y;
	}
}

void CapPiou::actualiser(std::vector<Projectile*>& projectiles, Entite& vaisseau, float tempsEcoule)
{
	// Création du projectile au moment où la compétence est lancée
	if (frames_ == 0)
	{
		ProjPiou *temp = new ProjPiou(debutX_, debutY_);
		projectiles.push_back(temp);
	}

	// Si la compétence est en cooldown, on actualise le timer
	if (t_ < cooldown_)
	{
		t_ += tempsEcoule;
		frames_++;
	}
		
}
