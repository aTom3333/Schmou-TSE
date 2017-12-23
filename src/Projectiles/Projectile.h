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

		virtual void gestion(sf::RenderWindow& window) = 0;
	protected:
		int age_;
};

#endif // PROJECTILE_H

