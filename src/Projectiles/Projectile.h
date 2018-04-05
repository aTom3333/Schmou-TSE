#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <vector>
#include <string>
#include <algorithm>
#include "../Entite.h"


// Déclaration préalable de Vaisseau pour éviter l'inclusion
class Vaisseau;


/**
* @class Projectile
* @brief Classe abstraite qui définit la structure générale d'un projectile, à faire hériter pour chaque projectile
*
* Classe abstraite mère de chaque projectile en tant qu'entité propre.
* Une capacité peut créer plusieurs projectiles ; elle leur donne des méthodes qui les font exister dans la boucle de jeu :
* déplacement, test de collison, dégats...
*
*/

class Projectile : public Entite
{
	public:
		explicit Projectile(Ecran& ecran) : Entite(ecran) {};

		virtual void gestion() = 0;
		/**
		* @fn destruction
		* @brief Procedure a effectuer lorsque le vaisseau est détruit
		*
		* Détruit l'entité
		*/
		void destruction() override { detruit_ = true; }

		/**
		*@fn gestion_aimbot
		*@brief Gestion de projectile en visée auto
		*/
		void gestion_aimbot();

	protected:
        std::weak_ptr<Entite> lanceur_; ///< On garde un lien vers le lanceur à travers un weak_ptr pour éviter les cycles
		bool aimbot_ = false;///<True si en état visée automatique

};

#endif // PROJECTILE_H

