#ifndef AIMBOT_H
#define AIMBOT_H

#include "Capacite.h"

//TODO PG outdated
/**
* @class CapAimBot
* @brief donne visée auto à un skill (missile)
*
* Capacité qui permet de donner un mode visée auto à un autre skill du vaisseau.
* Niveau 1 : seulement le prochain tir
* Niveau supérieurs : plusieurs tirs
*
* Cooldown : 10sec
*/


class CapAimBot : public Capacite
{
public:
	/**
	* @fn CapPiou::CapPiou
	* @brief Constructeur
	*
	* Initialisation de la capacité
	*/
	explicit CapAimBot(Ecran& ecran, const std::weak_ptr<Entite>& lanceur);
	/**
	* @fn utiliser
	* @brief Active la capacite
	* @param x Abscisse de la position où la capacite est utilisée
	* @param y Ordonnée de la position où la capacite est utilisée
	*
	* Fonction Initialise la position de départ et le timer
	*/
	void utiliser(proj_container& projectiles) override;
	/**
	* @fn actualiser
	* @brief Active les effets de la capacité
	*
	* Créer 1 ProjPiou à l'activation
	* Actualise le timer
	* @param projectile Vecteur de tout les projectiles présent à l'écran
	* @param vaisseau Vaisseau qui a activé la compétence
	*/
	void actualiser(proj_container& projectiles) override;
	/**
    * @fn CapAimBot::set_state_autoAim_true
    * @brief Destructeur
    *
    * change l'état autoaim à true
    */
    void set_state_autoAim_true(Capacite& capacite);
    /**
    * @fn CapAimBot::set_state_autoAim_false
    * @brief Destructeur
    *
    * change l'état autoaim à false
    */
    void set_state_autoAim_false(Capacite& capacite);

};

#endif //AIMBOT_H



