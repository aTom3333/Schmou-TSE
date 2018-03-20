#include <vector>
#include <string>
#include <algorithm>
#include "../Capacites/Capacite.h"
#include "Vaisseau.h"
#include "../Projectiles/Projectile.h"


Vaisseau::Vaisseau() ///constructeur
{
	//personnalisation
	//stats de base
	pvM_ = 100;
	atqM_ = 100;
	defM_ = 100;
	vitM_ = 100;
	//liste de capacités
}


Vaisseau::~Vaisseau() ///destructeur
{
	for(unsigned int i = 0; i < capacites_.size(); i++)
		delete capacites_[i];
}

void Vaisseau::gestionCapacite(std::vector <Projectile*> &projectiles, sf::Time t_ecoule)
{
	// Gestion des capacites
	for(unsigned int i = 0; i < capacites_.size(); i++)
		if (capacites_[i] != nullptr) capacites_[i]->actualiser(projectiles, *this, (float)t_ecoule.asMilliseconds());
}


void Vaisseau::agit(Entite & e)
{
	e.recoitDegats(degatsColl_);
}