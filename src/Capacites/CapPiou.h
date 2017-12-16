#ifndef CAPPIOU_H
#define CAPPIOU_H

#include "Capacite.h"
#include "../Projectiles/Projectile.h"
#include "../Projectiles/ProjPiou.h"

/**
* @class CapTest
* @brief Classe Capacit� de test
*
* Capacit� qui cr�� 1 ProjPiou � la postion du lanceur
* Nom : Attaque Piou
* Cooldown : 20
*/


class CapPiou : public Capacite
{
public:
	/**
	* @fn CapPiou::CapPiou
	* @brief Constructeur
	*
	* Initialisation de la capacit�
	*/
	CapPiou();
	/**
	* @fn CapPiou::~CapPiou
	* @brief Destructeur
	*
	* Vide
	*/
	~CapPiou();
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
	* Cr�er 1 ProjTest � l'activation
	* Actualise le timer
	*/
	void actualiser(std::vector<Projectile*> &projectiles, Entite *vaisseau, float tempsEcoule);
};

#endif //CAPPIOU
