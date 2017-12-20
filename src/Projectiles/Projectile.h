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
		Projectile();

		/**
		 * @fn agit
		 * @brief Réalise l'action que le @c Projectile doit faire sur le vaisseau
		 *
		 * Fonction virtuelle qui doit être surchargée pour les classes héritées.
		 * Elle réalise l'action que le @c Projectile appelant sur le @c Vaisseau passé en paramètre (dégats, changement de stat, ...)
		 * @param v Un @c Vaisseau sur lequel l'action du @c Projectile va se faire
		 */
		virtual void agit(Entite&) =0;
		virtual void gestion(sf::RenderWindow& window) = 0;
	protected:
		int age_;
};

#endif // PROJECTILE_H

