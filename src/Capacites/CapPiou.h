#ifndef CAPPIOU_H
#define CAPPIOU_H

#include "Capacite.h"
#include "../Projectiles/Projectile.h"

/**
* @class CapPiou
* @brief Classe Capacité de base
*
* Capacité qui créé 1 ProjPiou à la position du lanceur
* Nom : Attaque Piou
* Cooldown : 100 ms
*/

//TODO refaire la doc

class CapPiou : public Capacite
{
	public:
		/**
		* @fn CapPiou::CapPiou
		* @brief Constructeur
		*
		* Initialisation de la capacité
		*/
		explicit CapPiou(Ecran& ecran, const std::weak_ptr<Entite>& lanceur);
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
		*/
		void actualiser(proj_container& projectiles) override;
};

#endif //CAPPIOU
