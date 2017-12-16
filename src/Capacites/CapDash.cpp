#include "CapDash.h"

CapDash::CapDash()
{
	cooldown_ = 100;
	t_ = cooldown_;
	nom_ = "Dash";
}

CapDash::~CapDash()
{
}

void CapDash::utiliser(int x, int y)
{
	// Si la compétence est disponible
	if(t_ >= cooldown_)
		// Début du timer
		t_ = 0;
}


void CapDash::actualiser(std::vector<Projectile*>& projectiles, Entite * vaisseau)
{
	// Augmente la vitesse de 5000 à l'activation
	if(t_ == 0)
		vaisseau->changeSpeed(5000);
	// Retourne à la vitesse de base au bout de 5 frames
	if(t_ == 5)
		vaisseau->changeSpeed(-5000);

	// Si la compétance est en cooldown, on actualise le timer
	if (t_ < cooldown_)
		t_++;

}
