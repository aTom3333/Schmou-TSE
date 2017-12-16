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
	// Si la comp�tence est disponible
	if(t_ >= cooldown_)
		// D�but du timer
		t_ = 0;
}


void CapDash::actualiser(std::vector<Projectile*>& projectiles, Entite * vaisseau)
{
	// Augmente la vitesse de 5000 � l'activation
	if(t_ == 0)
		vaisseau->changeSpeed(5000);
	// Retourne � la vitesse de base au bout de 5 frames
	if(t_ == 5)
		vaisseau->changeSpeed(-5000);

	// Si la comp�tance est en cooldown, on actualise le timer
	if (t_ < cooldown_)
		t_++;

}
