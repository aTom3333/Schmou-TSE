#include "CapDash.h"

CapDash::CapDash()
{
	cooldown_ = 500;
	frames_ = cooldown_;
	t_ = cooldown_;
	nom_ = "Dash";
}


void CapDash::utiliser(int x, int y)
{
	// Si la compétence est disponible
	if (t_ >= cooldown_) {
		// Début du timer
		t_ = 0;
		frames_ = 0;
	}
}


void CapDash::actualiser(std::vector<Projectile*>& projectiles, Entite& vaisseau, float tempsEcoule)
{
	// Augmente la vitesse de 5000 à l'activation
	if(frames_ == 0)
		vaisseau.changeSpeed(5000);
	// Retourne à la vitesse de base au bout de 5 frames
	if(frames_ == 5)
		vaisseau.changeSpeed(-5000);

	// Si la compétence est en cooldown, on actualise le timer
	if (t_ < cooldown_)
	{
		t_ += tempsEcoule;
		frames_++;

	}
		

}
