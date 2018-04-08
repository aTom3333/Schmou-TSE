#ifndef CAPDASH_H
#define CAPDASH_H

#include "Capacite.h"
#include "../Entite.h"
#include "../Projectiles/ProjBoing.h"

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
		* @param [in] x Abscisse de la position où la capacite est utilisée
		* @param [in] y Ordonnée de la position où la capacite est utilisée
		*
		* Fonction Initialise la position de départ et le timer
		*/
		void utiliser(proj_container& projectiles) override;
		/**
		 * @fn actualiser
		 * @brief Active les effets de la capacité
		 * @param [in,out] projectile Vecteur de tout les projectiles présent à l'écran
		 * @param [in,out] vaisseau Vaisseau qui a activé la compétence
		 * @param [in] tempsEcoule Temps écoulé en millisecondes
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