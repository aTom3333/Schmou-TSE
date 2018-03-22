#ifndef CAPBISMILLAHBEAM_H
#define CAPBISMILLAHBEAM_H

#include "Capacite.h"

class CapBismillah : public Capacite
{
	public:
		CapBismillah();
	
		void utiliser(int x, int y) override;
		void actualiser(proj_container& projectiles, Entite& vaisseau, float tempsEcoule);
	private:

};

#endif // !CAPBISMILLAHBEAM_H
