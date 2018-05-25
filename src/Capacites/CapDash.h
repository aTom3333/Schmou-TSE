#ifndef CAPDASH_H
#define CAPDASH_H

#include "Capacite.h"
#include "../Entite.h"

/**
* @class CapDash
* @brief Classe Capacité permettant de dash
*
* Modifie la vitesse du vaisseau peandant quelques frames
* Nom : Dash
* Cooldown : 500 ms
*/

class CapDash : public Capacite
{
	public:
		/**
		* @fn CapDash::CapDash
		* @brief Constructeur
		*
		* Initialisation de la capacité
		*/
		CapDash(Ecran& ecran, const std::weak_ptr<Entite>& lanceur);
		/**
		* @fn utiliser
		* @brief Active la capacite
		* @param projectiles Vecteur de tout les projectiles présent à l'écran
		*
		* Fonction Initialise la position de départ et le timer
		*/
		void utiliser(proj_container& projectiles) override;
		/**
		 * @fn actualiser
		 * @brief Active les effets de la capacité
		 * @param [in,out] projectiles Vecteur de tout les projectiles présent à l'écran
		 *
		 * Augmente la vitesse du vaisseau pour quelques frames
		 * Actualise le timer
		 */
		void actualiser(proj_container& projectiles) override;
	private:
		bool active_; // true si le buff a été activé;
		sf::Texture smoke_; // trainée que laisse le joueur lors du dash
};

#endif