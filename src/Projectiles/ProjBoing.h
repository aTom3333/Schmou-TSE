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
		ProjBoing(); 
		/**
		* @fn ProjBoing
		* @brief Constructeur
		* @param x Abscisse de la postion de départ du projectile
		* @param y Ordonnée de la postion de départ du projectile
		*
		* Créer un projectile de test à la position donnée en paramètre
		*/
		ProjBoing(int x, int y, sf::Sound sound);
		/**
		* @fn ~ProjBoing
		* @brief Destructeur
		*
		* Vide
		*/
		~ProjBoing(); 
		/**
		* @fn gestion
		* @brief Gestion du projectile
		* @param window Fenetre de jeu
		* @param tempsEcoule Temps écoulé depuis le dernier appel
		*
		* Gestion du déplacement et de la collision avec les bords
		*/
		void gestion(sf::RenderWindow &window, sf::Time tempsEcoule);
		/**
		* @fn agit
		* @brief Procédure lorsque le projectile agit avec unvaisseau
		* @param Vaisseau à modifier
		*
		* Vide
		*/
		void agit(Entite& proj);
	private:
		int mx_; /// Multiplicateur (1 ou -1) pour gérer le sens du projectile
		int my_; /// Multiplicateur (1 ou -1) pour gérer le sens du projectile
		int vx_; /// Vitesse horizontale
		int vy_; /// Vitesse Verticale
};

#endif //PROJ_TEST_H