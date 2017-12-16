#ifndef CAPTEST_H
#define CAPTEST_H

#include "Capacite.h"
#include "../Projectiles/Projectile.h"
#include "../Projectiles/ProjTest.h"

/**
* @class CapTest
* @brief Classe Capacit� de test
*
* Capacit� qui cr�� 4 ProjTest � la postion du lanceur
* Nom : Attaque Test
* Cooldown : 100
*/

class CapTest : public Capacite
{
	public:
		/**
		* @fn CapTest::CapTest
		* @brief Constructeur
		*
		* Initialisation de la capacit�
		*/
		CapTest();
		/**
		* @fn CapTest::~CapTest
		* @brief Destructeur
		*
		* Vide
		*/
		~CapTest();
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
		* Cr�er 4 ProjTest toutes les 5 frames
		* Actualise le timer
		*/
		void actualiser(std::vector<Projectile*> &projectiles, Entite *vaisseau, float tempsEcoule);
};

#endif
