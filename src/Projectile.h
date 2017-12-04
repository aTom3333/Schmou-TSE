#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <vector>
#include <string>
#include <algorithm>


/**
* @class Projectile
* @brief Classe abstraite qui définit la structure générale d'un projectile, à faire hériter de chaque projectile
*
* Classe abstraite mère de chaque projectile en tant qu'entité propre.
* Une capacité peut créer plusieurs projectiles ; elle leur donne des méthodes qui les font exister dans la boucle de jeu :
* déplacement, test de collison, dégats...
*
*/

class Projectile
{
	public:
		Projectile();
		~Projectile();

	private:

};

#endif // PROJECTILE_H

