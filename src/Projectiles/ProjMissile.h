#ifndef PROJ_MISSILE_H
#define PROJ_MISSILE_H

#include "Projectile.h"

/**
* @class ProjPiou
* @brief Projectile de test
*
* Projectile de base. Tire en ligne droite (vers le bas) avec qui une acceleration verticale
*/

class ProjMissile : public Projectile
{
	public:
		ProjMissile();
		ProjMissile(float x, float y);
		~ProjMissile();
		void gestion(sf::RenderWindow& window);
		void agit(Entite &e);
	private:
		float a_;
		float v_;
		int sens_;
};

#endif // PROJ_MISSILE_H