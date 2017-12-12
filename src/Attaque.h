#ifndef ATTAQUE_H
#define ATTAQUE_H

#include <string>

class Attaque
{
	public:
		int const getCooldown() { return cooldown_; };
		int const getTime() { return t_; };
		std::string const getNom() { return nom_; };
	protected:
		int debutX_, debutY_;
		int cooldown_;
		int t_;
		std::string nom_;
};

#endif