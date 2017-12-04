#ifndef VAISSEAU_H
#define VAISSEAU_H

#include <vector>
#include <string>
#include <algorithm>
#include "Capacite.h"
#include "Projectile.h"


/**
 * @class Vaisseau
 * @brief classe du vaisseau (véhicule) d'un joueur ou d'un ennemi
 *
 * Description détaillée 
 */

class Vaisseau
{
	public:
		Vaisseau(bool player);
		~Vaisseau();

	private:
		//personnalisation
		bool player_;
		std::string nom_;
		int Nskin_;
		//stats de base
		int pvM_;
		int atqM_;
		int defM_;
		int vitM_;
		//stats actualisées en jeu
		int pv_;
		int atq_;
		int def_;
		int vit_;
		//liste de capacités
		std::vector <Capacite> skills_;
};

#endif // VAISSEAU_H
