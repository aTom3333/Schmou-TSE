#include "CapPiou.h"

CapPiou::CapPiou()
{
	capText_.loadFromFile("../../rc/Capacites/tir.png");
	capacite_.setTexture(capText_);
	cooldown_ = 100;
	t_ = cooldown_;
	frames_ = cooldown_; //TODO ici le warning pourrait être important (float vers uint)
	nom_ = "Canon Laser";
	tir_ = true;
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
		//TODO bug
		ProjPiou *temp = new ProjPiou(debutX_, debutY_, vaisseau.getEquipe());
		projectiles.push_back(temp);
	}

	// Si la compétence est en cooldown, on actualise le timer
	if (t_ < cooldown_)
	{
		t_ += tempsEcoule;
	}
	frames_++;
}
