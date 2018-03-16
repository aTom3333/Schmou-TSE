#ifndef CAPBISMILLAHBEAM_H
#define CAPBISMILLAHBEAM_H

#include "Capacite.h"

class CapBismillah : public Capacite
{
public:
	CapBismillah();

	void utiliser(int x, int y);
	void actualiser(std::vector<Projectile*>& projectiles, Entite& vaisseau, float tempsEcoule);
private:

};

#endif // !CAPBISMILLAHBEAM_H
