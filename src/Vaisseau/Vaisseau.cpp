#include <vector>
#include <string>
#include <algorithm>
#include "../Capacites/Capacite.h"
#include "Vaisseau.h"
#include "../Projectiles/Projectile.h"

void Vaisseau::gestionCapacite(proj_container &projectiles)
{
	// Gestion des capacites
	for(unsigned int i = 0; i < capacites_.size(); i++)
		if (capacites_[i] != nullptr) capacites_[i]->actualiser(projectiles);
}


void Vaisseau::agit(Entite & e)
{
	e.recoitDegats(degatsColl_);
}