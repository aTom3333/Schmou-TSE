#ifndef ATTAQUE_H
#define ATTAQUE_H

#include <string>

class Attaque
{
	public:
	
	protected:
		int debutX_, debutY_;
		int cooldown_;
		int t_;
		std::string nom_;
};

#endif