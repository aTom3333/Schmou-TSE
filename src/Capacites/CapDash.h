#ifndef CAPDASH_H
#define CAPDASH_H

#include "Capacite.h"
#include "../Entite.h"
#include "../Projectiles/ProjTest.h"

/**
* @class CapTest
* @brief Classe Capacité de test
*
* Capacité qui créé 1 ProjPiou à la postion du lanceur
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
	* Initialisation de la capacité
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
	* @param x Abscisse de la postion où la capacite est utilisée
	* @param y Ordonnée de la postion où la capacite est utilisée
	*
	* Fonction Initialise la postion de départ et le timer
	*/
	void utiliser(int x, int y);
	/**
	* @fn actualiser
	* @brief Active les effets de la capacité
	* @param projectile Vecteur de tout les projectiles présent à l'écran
	* @param vaisseau Vaisseau qui a activé la compétance
	*
	* Augmente la vitesse du vaisseau pour quelques frames
	* Actualise le timer
	*/
	void actualiser(std::vector<Projectile*> &projectiles, Entite *vaisseau, float tempsEcoule);
};

#endif