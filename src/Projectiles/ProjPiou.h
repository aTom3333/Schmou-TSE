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
	* @param x Abscisse de la postion de départ du projectile
	* @param y Ordonnée de la postion de départ du projectile
	*
	* Créer un projectile piou à la position donnée en paramètre
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
	* Gestion du déplacement et de l'affichage
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
	int vx_; /// Vitesse horizontale
	int vy_; /// Vitesse verticale
};

#endif