#ifndef ATKPIOU_H
#define ATKPIOU_H

#include "Attaque.h"
#include "Projectile.h"
#include "ProjPiou.h"

class AtkPiou : public Attaque
{
public:
	AtkPiou();
	~AtkPiou();
	void utiliser(int x, int y);
	void actualiser(std::vector<Projectile*> &projectiles);
};

#endif
