#ifndef CAP_MISSILE_H
#define CAP_MISSILE_H

#include "Capacite.h"
#include "../Projectiles/ProjMissile.h"

/**
* @class CapMissile
* @brief Classe Capacit� de base
*
* Capacit� qui cr�� 1 ProjMissile � la postion du lanceur
* Nom : Missile
* Cooldown : 5000 ms
*/

class CapMissile : public Capacite
{
	public:
		CapMissile();
		/**
		* @fn utiliser
		* @brief Active la capacite
		* @param x Abscisse de la postion o� la capacite est utilis�e
		* @param y Ordonn�e de la postion o� la capacite est utilis�e
		*
		* Fonction Initialise la postion de d�part et le timer
		*/
		void utiliser(int x, int y) override;
		/**
		* @fn actualiser
		* @brief Active les effets de la capacit�
		*
		* Cr�er 1 ProjBouclierRond � l'activation
		* Actualise le timer
		* @param projectile Vecteur de tout les projectiles pr�sent � l'�cran
		* @param vaisseau Vaisseau qui a activ� la comp�tance
		*/
		void actualiser(std::vector<Projectile*>& projectiles, Entite& vaisseau, float tempsEcoule) override;
	private:

};


#endif // CAP_MISSILE_H