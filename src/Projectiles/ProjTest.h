#ifndef PROJ_TEST_H
#define PROJ_TEST_H

#include "Projectile.h"

class Vaisseau;

/**
* @class ProjTest
* @brief Projectile de test
*
* Lance 4 boules qui rebondissent sur les bord de l'écran
*/

class ProjTest : public Projectile
{
	public:
		/**
		* @fn ProjTest::Projtest
		* @brief Constructeur
		*
		* Créer un projectile de test à une position aléatoire
		*/
		ProjTest(); 
		/**
		* @fn ProjTest
		* @brief Constructeur
		* @param x Abscisse de la postion de départ du projectile
		* @param y Ordonnée de la postion de départ du projectile
		*
		* Créer un projectile de test à la position donnée en paramètre
		*/
		ProjTest(int x, int y); 
		/**
		* @fn ~ProjTest
		* @brief Destructeur
		*
		* Vide
		*/
		~ProjTest(); 
		/**
		* @fn gestion
		* @brief Gestion du projectile
		* @param window Fenetre de jeu
		*
		* Gestion du déplacement et de la collision avec les bords
		*/
		void gestion(sf::RenderWindow &window);
		/**
		* @fn agit
		* @brief Procédure lorsque le projectile agit avec unvaisseau
		* @param Vaisseau à modifier
		*
		* Vide
		*/
		void agit(Vaisseau &v) {};
	private:
		int mx_; /// Multiplicateur (1 ou -1) pour gérer le sens du projectile
		int my_; /// Multiplicateur (1 ou -1) pour gérer le sens du projectile
		int vx_; /// Vitesse horizontale
		int vy_; /// Vitesse Verticale
};

#endif //PROJ_TEST_H