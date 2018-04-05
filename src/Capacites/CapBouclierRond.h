#ifndef BOUCLIER_ROND_H
#define BOUCLIER_ROND_H

#include "Capacite.h"
#include "../Projectiles/Projectile.h"
#include "../Projectiles/ProjBouclierRond.h"


/**
* @class CapBouclierRond
* @brief bouclier circulaire avec x PB
*
* Donne un bouclier circulaire qui entoure le vaisseau. Il est supprimé après un certain temps ( s sec) ou si ses (pb) PB tombent à zéro.
* Le bouclier est un projectile.
* Niveau 1 :
* Niveau supérieurs (idées) : augmente PB, temps de stase, réduit CD
*
* Cooldown : 10sec
*/

class CapBouclierRond : public Capacite
{
	public:
		/**
		* @fn CapBouclierRond::CapBouclierRond
		* @brief Constructeur
		* @param niveau niveau de la capacité
		* @param Entite_liee_ Entite à laquelle s'applique le bouclier
		*
		* Initialisation
		*/
		CapBouclierRond(Ecran& ecran, const std::weak_ptr<Entite>& lanceur);
	

		void utiliser(proj_container& projectiles) override;

		void actualiser(proj_container& projectiles) override;
};

#endif //BOUCLIER_ROND_H



