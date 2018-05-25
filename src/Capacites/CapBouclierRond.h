#ifndef BOUCLIER_ROND_H
#define BOUCLIER_ROND_H

#include "Capacite.h"
#include "../Projectiles/Projectile.h"


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
		* @param ecran Référence vers un écran où se trouve le lanceur
		* @param lanceur lanceur de la capacité
		*
		* Initialisation
		*/
		CapBouclierRond(Ecran& ecran, const std::weak_ptr<Entite>& lanceur);	

		void utiliser(proj_container& projectiles) override;

		void actualiser(proj_container& projectiles) override;
};

#endif //BOUCLIER_ROND_H



