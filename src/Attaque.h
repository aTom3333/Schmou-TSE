#ifndef ATTAQUE_H
#define ATTAQUE_H

#include <string>
#include <vector>
#include "Projectile.h"

class Attaque
{
	public:
		int const getCooldown() { return cooldown_; };
		int const getTime() { return t_; };
		std::string const getNom() { return nom_; };
		virtual void utiliser(int x, int y) = 0;
		virtual void actualiser(std::vector<Projectile*> &projectiles) = 0;
	protected:
		int debutX_, debutY_;
		int cooldown_;
		int t_;
		std::string nom_;
};

#endif