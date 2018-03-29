#include <vector>
#include <string>
#include <algorithm>
#include "../Capacites/Capacite.h"
#include "Vaisseau.h"
#include "../Projectiles/Projectile.h"

void Vaisseau::gestionCapacite(proj_container &projectiles)
{
	for(auto& capacite : capacites_) 
		if(capacite != nullptr) capacite->actualiser(projectiles);
}


void Vaisseau::agit(Entite & e)
{
	e.recoitDegats(degatsColl_);
}