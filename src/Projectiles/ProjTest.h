#ifndef PROJ_TEST_H
#define PROJ_TEST_H

#include "Projectile.h"

class Vaisseau;

/**
* @class ProjTest
* @brief Projectile de test
*
* Lance 4 boules qui rebondissent sur les bord de l'�cran
*/

class ProjTest : public Projectile
{
	public:
		/**
		* @fn ProjTest::Projtest
		* @brief Constructeur
		*
		* Cr�er un projectile de test � une position al�atoire
		*/
		ProjTest(); 
		/**
		* @fn ProjTest
		* @brief Constructeur
		* @param x Abscisse de la postion de d�part du projectile
		* @param y Ordonn�e de la postion de d�part du projectile
		*
		* Cr�er un projectile de test � la position donn�e en param�tre
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
		* Gestion du d�placement et de la collision avec les bords
		*/
		void gestion(sf::RenderWindow &window);
		/**
		* @fn agit
		* @brief Proc�dure lorsque le projectile agit avec unvaisseau
		* @param Vaisseau � modifier
		*
		* Vide
		*/
		void agit(Vaisseau &v) {};
	private:
		int mx_; /// Multiplicateur (1 ou -1) pour g�rer le sens du projectile
		int my_; /// Multiplicateur (1 ou -1) pour g�rer le sens du projectile
		int vx_; /// Vitesse horizontale
		int vy_; /// Vitesse Verticale
};

#endif //PROJ_TEST_H