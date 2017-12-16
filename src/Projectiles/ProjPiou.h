#ifndef PROJ_PIOU_H
#define PROJ_PIOU_H

#include "Projectile.h"

/**
* @class ProjTest
* @brief Projectile de test
*
* Projectile de base. Tire en ligne droite (vers le haut)
*/



class ProjPiou : public Projectile
{
public:
	/**
	* @fn ProjTest
	* @brief Constructeur
	*
	* Vide
	*/
	ProjPiou();
	/**
	* @fn ProjTest
	* @brief Constructeur
	* @param x Abscisse de la postion de d�part du projectile
	* @param y Ordonn�e de la postion de d�part du projectile
	*
	* Cr�er un projectile piou � la position donn�e en param�tre
	*/
	ProjPiou(int x, int y);
	/**
	* @fn ~ProjTest
	* @brief Destructeur
	*
	* Vide
	*/
	~ProjPiou();
	/**
	* @fn gestion
	* @brief Gestion du projectile
	* @param window Fenetre de jeu
	*
	* Gestion du d�placement et de l'affichage
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
	int vx_; /// Vitesse horizontale
	int vy_; /// Vitesse verticale
};

#endif
