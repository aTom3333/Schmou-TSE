#ifndef PROJ_PIOU_H
#define PROJ_PIOU_H

#include "Projectile.h"

/**
* @class ProjPiou
* @brief Projectile de test
*
* Projectile de base. Tire en ligne droite (vers le haut)
*/



class ProjPiou : public Projectile
{
public:
	/**
	* @fn ProjPiou
	* @brief Constructeur
	*
	* Vide
	*/
	ProjPiou();
	/**
	* @fn ProjPiou
	* @brief Constructeur
	* @param x Abscisse de la postion de départ du projectile
	* @param y Ordonnée de la postion de départ du projectile
	*
	* Créer un projectile piou à la position donnée en paramètre
	*/
	ProjPiou(int x, int y, Equipe equipe);
	/**
	* @fn ~ProjPiou
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
	void gestion(sf::RenderWindow &window, sf::Time tempsEcoule);
	/**
	* @fn agit
	* @brief Procédure lorsque le projectile agit avec une Entite
	* @param e Entite à modifier
	*
	* Vide
	*/
	void agit(Entite &e);
private:
	int vx_; /// Vitesse horizontale
	int vy_; /// Vitesse verticale
};

#endif
