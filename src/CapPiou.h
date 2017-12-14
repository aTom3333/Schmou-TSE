#ifndef CAPPIOU_H
#define CAPPIOU_H

#include "Capacite.h"
#include "Projectile.h"
#include "ProjPiou.h"

class CapPiou : public Capacite
{
public:
	CapPiou();
	~CapPiou();
	void utiliser(int x, int y);
	void actualiser(std::vector<Projectile*> &projectiles, Entite *vaisseau);
};

#endif //CAPPIOU
