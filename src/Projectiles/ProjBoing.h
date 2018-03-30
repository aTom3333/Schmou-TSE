#ifndef PROJ_BOING_H
#define PROJ_BOING_H

#include "Projectile.h"

class Vaisseau;

/**
* @class ProjBoing
* @brief Projectile de test
*
* Lance 4 boules qui rebondissent sur les bord de l'écran
*/

class ProjBoing : public Projectile
{
	public:
		/**
		* @fn ProjBoing::Projtest
		* @brief Constructeur
		*
		* Créer un projectile de test à une position aléatoire
		*/
		ProjBoing(Ecran& ecran, std::shared_ptr<Entite> lanceur, std::vector<sf::Sprite>& sprite, std::vector<sf::Sound>& sound, Equipe equipe = NEUTRE);
		/**
		* @fn ~ProjBoing
		* @brief Destructeur
		*
		* Vide
		*/
		~ProjBoing() {};
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
		* @brief Procédure lorsque le projectile agit avec unvaisseau
		* @param Vaisseau à modifier
		*
		* Vide
		*/
		void agit(Entite& proj);
	private:
		float rayonCirc_; /// < rayon du cerlce circonscrit au lanceur où est lancé le projectile
		float rotationSpr_ = 0; /// Rotation du sprite
};

#endif //PROJ_TEST_H