#ifndef CAP_MISSILE_H
#define CAP_MISSILE_H

#include "Capacite.h"
#include "../Projectiles/ProjMissile.h"

/**
* @class CapMissile
* @brief Classe Capacité de base
*
* Capacité qui créé 1 ProjMissile à la postion du lanceur
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
		* @param x Abscisse de la postion où la capacite est utilisée
		* @param y Ordonnée de la postion où la capacite est utilisée
		*
		* Fonction Initialise la postion de départ et le timer
		*/
		void utiliser(int x, int y) override;
		/**
		* @fn actualiser
		* @brief Active les effets de la capacité
		*
		* Créer 1 ProjPiou à l'activation
		* Actualise le timer
		* @param projectile Vecteur de tout les projectiles présent à l'écran
		* @param vaisseau Vaisseau qui a activé la compétence
		*/
		void actualiser(std::vector<Projectile*>& projectiles, Entite& vaisseau, float tempsEcoule) override;
	private:

};


#endif // CAP_MISSILE_H