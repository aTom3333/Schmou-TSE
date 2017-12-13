#ifndef CAPACITE_H
#define CAPACITE_H

#include <vector>
#include <string>
#include <algorithm>
#include "Projectile.h"
#include "Entite.h"


/**
 * @class Capacite
 * @brief Classe abstraite qui définit la structure générale d'une capacité, à faire hériter de chaque capacité
 *
 * Cette classe abstraite permet de définir la structure générale d'une capacité du jeu,
 * elle doit être héritée pour chaque capacité qui est ajoutée au jeu
 */
class Capacite
{
	public:
		Capacite() = default;
		virtual ~Capacite() = default;
		int const getCooldown() { return cooldown_; };
		int const getTime() { return t_; };
		std::string const getNom() { return nom_; };
		virtual void utiliser(int x, int y) = 0;
		virtual void actualiser(std::vector<Projectile*> &projectiles, Entite *vaisseau) = 0;
	protected:
		int debutX_, debutY_;
		int cooldown_;
		int t_;
		std::string nom_;

};

#endif // CAPACITE_H
