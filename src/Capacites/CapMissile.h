#ifndef CAP_MISSILE_H
#define CAP_MISSILE_H

#include "Capacite.h"
#include "../Projectiles/ProjMissile.h"

/**
* @class CapMissile
* @brief Classe Capacité de base
*
* Capacité qui créé 1 ProjMissile à la position du lanceur
* Nom : Missile
* Cooldown : 5000 ms
*/

class CapMissile : public Capacite
{
	public:
		CapMissile(Ecran& ecran, const std::weak_ptr<Entite>& lanceur);
		/**
		* @fn utiliser
		* @brief Active la capacité
		* @param projectiles Vecteur de tout les projectiles présent à l'écran
		*
		* Fonction Initialise la position de départ et le timer
		*/
		void utiliser(proj_container& projectiles) override;
		/**
		* @fn actualiser
		* @brief Active les effets de la capacité
		*
		* Créer 1 ProjPiou à l'activation
		* Actualise le timer
		* @param projectiles Vecteur de tout les projectiles présent à l'écran
		*/
		void actualiser(proj_container& projectiles) override;
};


#endif // CAP_MISSILE_H