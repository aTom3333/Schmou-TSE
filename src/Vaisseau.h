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
		explicit Vaisseau(bool player);
		~Vaisseau();

	private:
		// personnalisation
		bool player_; /// < Booléen qui définit si le vaisseau est un joueur ou non
		std::string nom_; /// < Nom du vaisseau ?
		int Nskin_; /// < Je ne sais pas
		// stats de base
		int pvM_; /// < Points de vie de base
		int atqM_; /// < Attaque de base
		int defM_; /// < Défense de base
		int vitM_; /// < Vitesse de base
		// stats actualisées en jeu
		int pv_; /// < Points de vie actuels
		int atq_; /// < Attaque actuelle
		int def_; /// < Défense actuelle
		int vit_; /// < Vitesse actuelle
		// liste de capacités
		std::vector<Capacite> skills_; /// < Liste des capacités du vaisseau
};

#endif // VAISSEAU_H
