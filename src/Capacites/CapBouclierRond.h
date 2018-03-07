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
protected :
	int pvM_; ///pv max du bouclier
	int cooldown_; /// cooldown
	int degatsColl_; /// dégats infligés lors d'une collisison avec une Entite collisionnable
	Entite* Entite_liee_; /// Entite à laquelle s'applique le bouclier

public:



	/**
	* @fn CapBouclierRond::CapBouclierRond
	* @brief Constructeur
	* @param niveau niveau de la capacité
	* @param Entite_liee_ Entite à laquelle s'applique le bouclier
	*
	* Initialisation
	*/
	CapBouclierRond(int niveau, Entite* Entite_liee);
	

	void utiliser(int x, int y) override;

	void actualiser(std::vector<Projectile*>& GVP, Entite& vaisseau, float tempsEcoule);

	



};

#endif BOUCLIER_ROND_H



