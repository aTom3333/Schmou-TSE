#ifndef AIMBOT_H
#define AIMBOT_H

#include "Capacite.h"

/**
* @class CapAimBot
* @brief donne vis�e auto � un skill (missile)
*
* Capacit� qui permet de donner un mode vis�e auto � un autre skill du vaisseau.
* Niveau 1 : seulement le prochain tir
* Niveau sup�rieurs : plusieurs tirs
*
* Cooldown : 10sec
*/


class CapAimBot : public Capacite
{
private:
	bool autoAim_;
public:



	/**
	* @fn CapAimBot::CapAimBot
	* @brief Constructeur
	*
	* Vide
	*/
	CapAimBot();
	/**
	* @fn CapAimBot::~CapAimBot
	* @brief Destructeur
	*
	* Vide
	*/
	~CapAimBot()
	{
	}
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



