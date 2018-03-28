#ifndef PROJ_BOUCLIER_ROND_H
#define PROJ_BOUCLIER_ROND_H

#include "Projectile.h"

class ProjBouclierRond : public Projectile
{
public:
	~ProjBouclierRond() override { sounds_.front().stop(); };

	/**
	* @fn ProjBouclierRond
	* @brief Constructeur
	* @param Entite_liee entite sur laquelle s'applique le bouclier
	* @param pvM pv max
	* @param degatsColl dégats infligés lors d'une collision avec une Entite collisionnable
	* Gestion du déplacement et de l'affichage
	*/
	ProjBouclierRond(Ecran& ecran, std::shared_ptr<Entite> lanceur, std::vector<sf::Sprite>& sprite, std::vector<sf::Sound>& sound, Equipe equipe);

	/**
	* @fn gestion
	* @brief Gestion du projectile
	* @param window Fenetre de jeu
	*
	* Gestion du déplacement et de l'affichage : le bouclier reste lié à l'Entite_liee
	*/
	void gestion();

	/**
	* @fn agit
	* @brief Action lorsque collision avec une Entite collisionnable
	* @param e Entite 
	*
	* Inflige les dégat déterminés à la construction
	*/
	void agit(Entite &e);

protected:
	float tempsMax_;
};


#endif // !PROJ_BOUCLIER_ROND_H

