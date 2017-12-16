#ifndef CAPTEST_H
#define CAPTEST_H

#include "Capacite.h"
#include "../Projectiles/Projectile.h"
#include "../Projectiles/ProjTest.h"

/**
* @class CapTest
* @brief Classe Capacité de test
*
* Capacité qui créé 4 ProjTest à la postion du lanceur
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
		* Initialisation de la capacité
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
		* Créer 4 ProjTest toutes les 5 frames
		* Actualise le timer
		*/
		void actualiser(std::vector<Projectile*> &projectiles, Entite *vaisseau, float tempsEcoule);
};

#endif
