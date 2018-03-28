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
		ProjMissile(Ecran& ecran, std::shared_ptr<Entite> lanceur, std::vector<sf::Sprite>& sprite, std::vector<sf::Sound>& sound, Equipe equipe);
		~ProjMissile() {};
		/**
		* @fn gestion
		* @brief Gestion du projectile
		* @param window Fenetre de jeu
		* @param tempsEcoule Temps écoulé depuis le dernier appel
		*
		* Gestion du déplacement et de la collision avec les bords
		*/
		void gestion();
		/**
		* @fn agit
		* @brief Procédure lorsque le projectile agit avec une Entite
		* @param e Entite à modifier
		*
		* Vide
		*/
		void agit(Entite &e);
	private:
		float coef_acceleration_;
};

#endif // PROJ_MISSILE_H