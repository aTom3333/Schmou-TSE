#ifndef VAISS_BOUCLIER_H
#define VAISS_BOUCLIER_H

#include "Vaisseau.h"

/**
* @class VaissBouclier
* @brief classe du bouclier du VaisseauDefenseur
*
* Bouclier : Module d'un vaisseau ennemi
* Comportement : Pas de déplacement Pas de tir
*/

class VaissBouclier : public Vaisseau
{
public:
	/**
	* @fn VaissBouclier
	* @brief Contructeur
	* Initialise le vaisseau à position et à la trajectoires désirées
	*/
	VaissBouclier(Ecran& ecran);
	/**
	* @fn ~VaisseauEclaireur
	* @brief Destructeur
	*
	* Vide
	*/
	~VaissBouclier() {};
	/**
	* @fn gestion
	* @brief Gère le comportement du vaisseau
	* @param window Fenetre SFML où le vaisseau sera affiché
	* @param tempsEcoule Temps écoulé depuis le dernier appel
	* @param input Classe Input donnant accés aux entrée
	*
	* Gère le déplacement et l'affichage du vaisseau
	*/
	void gestion(proj_container proj_cont, Input& input);
	/**
	* @fn destruction
	* @brief Procedure a effectuer lorsque le vaisseau est détruit
	*
	* Indique au créateur que l'annexe est détuite
	*/
	void destruction() { detruit_ = true; }
};


#endif // VAISS_BOUCLIER_H