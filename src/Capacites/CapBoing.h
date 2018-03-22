#ifndef CAPTEST_H
#define CAPTEST_H

#include "Capacite.h"
#include "../Projectiles/Projectile.h"
#include "../Projectiles/ProjBoing.h"

/**
* @class CapBoing
* @brief Classe Capacité de test
*
* Capacité qui créé 4 ProjBoing à la position du lanceur
* Nom : Attaque Test
* Cooldown : 1000 ms
*/

class CapBoing : public Capacite
{
	public:
		/**
		* @fn CapBoing::CapBoing
		* @brief Constructeur
		*
		* Initialisation de la capacité
		*/
		CapBoing();
		/**
		* @fn CapBoing::~CapBoing
		* @brief Destructeur
		*
		* Vide
		*/
		~CapBoing();
		/**
		* @fn utiliser
		* @brief Active la capacite
		* @param x Abscisse de la position où la capacite est utilisée
		* @param y Ordonnée de la position où la capacite est utilisée
		*
		* Fonction Initialise la position de départ et le timer
		*/
		void utiliser(int x, int y);
		/**
		* @fn actualiser
		* @brief Active les effets de la capacité
		* @param projectile Vecteur de tout les projectiles présent à l'écran
		* @param vaisseau Vaisseau qui a activé la compétence
		*
		* Créer 4 ProjBoing toutes les 5 frames
		* Actualise le timer
		*/
		void actualiser(proj_container& projectiles, Entite& vaisseau, float tempsEcoule);
};

#endif
