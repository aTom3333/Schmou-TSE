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
		bool _player;
		std::string _nom;
		int _Nskin;
		//stats de base
		int _pvM;
		int _atqM;
		int _defM;
		int _vitM;
		//stats actualisées en jeu
		int _pv;
		int _atq;
		int _def;
		int _vit;
		//liste de capacités
		std::vector <Capacite> _skills;
};

#endif // VAISSEAU_H
