#ifndef PROJ_MISSILE_H
#define PROJ_MISSILE_H

#include "Projectile.h"

/**
* @class ProjMissile
* @brief Missile guidé
*
* Projectile de base. Tire en ligne droite (vers le bas) avec qui une acceleration verticale
*/

class ProjMissile : public Projectile
{
	public:
		ProjMissile(Ecran& ecran, std::shared_ptr<Entite> lanceur, std::vector<sf::Sprite>& sprite, std::vector<sf::Sound>& sound, Equipe equipe, bool aimbot = false);
		~ProjMissile() {};
		/**
		* @fn gestion
		* @brief Gestion du projectile
		*
		* Gestion du déplacement et de la collision avec les bords
		*/
		void gestion() override;
		/**
		* @fn agit
		* @brief Procédure lorsque le projectile agit avec une Entite
		* @param e Entite à modifier
		*
		* Vide
		*/
		void agit(Entite &e) override;
	private:
		std::weak_ptr<Entite> cible_;
		sf::Time t_acceleration_;
};

#endif // PROJ_MISSILE_H