#ifndef CAPDASH_H
#define CAPDASH_H

#include "Capacite.h"
#include "../Entite.h"
#include "../Projectiles/ProjTest.h"

/**
* @class CapTest
* @brief Classe Capacit� de test
*
* Capacit� qui cr�� 1 ProjPiou � la postion du lanceur
* Nom : Dash
* Cooldown : 100
*/

class CapDash : public Capacite
{
public:
	/**
	* @fn CapDash::CapDash
	* @brief Constructeur
	*
	* Initialisation de la capacit�
	*/
	CapDash();
	/**
	* @fn CapDash::~CapDash
	* @brief Destructeur
	*
	* Vide
	*/
	~CapDash();
	/**
	* @fn utiliser
	* @brief Active la capacite
	* @param x Abscisse de la postion o� la capacite est utilis�e
	* @param y Ordonn�e de la postion o� la capacite est utilis�e
	*
	* Fonction Initialise la postion de d�part et le timer
	*/
	void utiliser(int x, int y);
	/**
	* @fn actualiser
	* @brief Active les effets de la capacit�
	* @param projectile Vecteur de tout les projectiles pr�sent � l'�cran
	* @param vaisseau Vaisseau qui a activ� la comp�tance
	*
	* Augmente la vitesse du vaisseau pour quelques frames
	* Actualise le timer
	*/
	void actualiser(std::vector<Projectile*> &projectiles, Entite *vaisseau, float tempsEcoule);
};

#endif