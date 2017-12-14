#ifndef CAPDASH_H
#define CAPDASH_H

#include "Capacite.h"
#include "Entite.h"
#include "ProjTest.h"

class CapDash : public Capacite
{
public:
	CapDash();
	~CapDash();
	void utiliser(int x, int y);
	void actualiser(std::vector<Projectile*> &projectiles, Entite *vaisseau);
};

#endif