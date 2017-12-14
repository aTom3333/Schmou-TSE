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
	if(t_ >= cooldown_)
		t_ = 0;
}


void CapDash::actualiser(std::vector<Projectile*>& projectiles, Entite * vaisseau)
{
	if(t_ == 0)
		vaisseau->changeSpeed(5000);
	if(t_ == 5)
		vaisseau->changeSpeed(-5000);

	if (t_ < cooldown_)
		t_++;

}
