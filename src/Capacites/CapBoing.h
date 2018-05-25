#ifndef CAPTEST_H
#define CAPTEST_H

#include "Capacite.h"
#include "../Projectiles/Projectile.h"

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
		CapBoing(Ecran& ecran, const std::weak_ptr<Entite>& lanceur);
		/**
		* @fn CapBoing::~CapBoing
		* @brief Destructeur
		*
		* Vide
		*/
		~CapBoing() override = default;
		/**
		* @fn utiliser
		* @brief Active la capacité
		* @param projectiles Vecteur de tout les projectiles présents à l'écran
		*
		* Fonction Initialise la position de départ et le timer
		*/
		void utiliser(proj_container& projectiles) override;
		/**
		* @fn actualiser
		* @brief Active les effets de la capacité
		* @param projectiles Vecteur de tout les projectiles présents à l'écran
		*
		* Crée 4 ProjBoing toutes les 5 frames
		* Actualise le timer
		*/
		void actualiser(proj_container& projectiles) override;
};

#endif
