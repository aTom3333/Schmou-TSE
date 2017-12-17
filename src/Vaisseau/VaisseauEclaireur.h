#ifndef VAISSEAU_ECRAIREUR_H
#define VAISSEAU_ECRAIREUR_H

#include "../constantes.h"
#include "Vaisseau.h"

/**
* @class VaisseauEclaireur
* @brief classe d'un ennemi de base : l'�claireur
*
* Eclaireur : Vaisseau ennemi
* Comportement : D�placement (Lin�aire, Parabolique, Sinsoidale) uniquement : pas de tir
*/

class VaisseauEclaireur : public Vaisseau
{
public:
	/**
	* @fn VaisseauEclaireur
	* @brief Contructeur
	* @param x Abscisse de la position de d�part
	* @param y Ordonn�e de la position de d�part
	* @param traj Trajectoire voulue (Lin�aire, parabolique ou sinusoidale)
	* @param param1 Lineaire : Pente		Parabolique : Abscisse de l'extremum		Sinusoidale : Pente
	* @param param2 Lineaire : Sens (1/-1)	Parabolique : Ordonn�e de l'extremum		Sinusoidale : P�riode spatiale
	* @param param3 Lineaire : Inutilis�	Parabolique : Sens (1/-1)					Sinusoidale : Amplitude
	* @param param4 Lineaire : Inutilis�	Parabolique : Inutilis�						Sinusoidale : Sens (1/-1)
	*
	* Initialise le vaisseau � position et � la trajectoires d�sir�es
	* Equations si le vaisseau est en fonction du temps �coul� depuis la cr�ation:
		- Lineraire : 
			x = x0 + param2*v*t
			y = param1*(x - x0) + y0
		- Parabolique :
			x = x0 + param3*v*t (faux mais approximation si la parabole est assez large)
			y = (y0 - param2)/(x0 - param1)^2 * (x - param1)^2 + param2
		- Sinusoidale :
			x = x0 + param4*v*t (faux mais approximation si la diff�rence de temps est tr�s petite devant la p�riode)
			y = param1 * (x - x0) + y0 + param3 * sin(2*pi/param2 * x)
	*/
	VaisseauEclaireur(float x, float y, Trajectoire traj, float param1, float param2, float param3 = 0, float param4 = 0);
	/**
	* @fn ~VaisseauEclaireur
	* @brief Destructeur
	*
	* Vide
	*/
	~VaisseauEclaireur();
	/**
	* @fn gestion
	* @brief G�re le comportement du vaisseau
	* @param window Fenetre SFML o� le vaisseau sera affich�
	* @param tempsEcoule Temps �coul� depuis le dernier appel
	*
	* G�re le d�placement et l'affichage du vaisseau
	*/
	void gestion(sf::RenderWindow & window, float tempsEcoule);
private:
	float x0_; /// Abscisse de d�part
	float y0_; /// Ordonn�e de d�part
	float param1_;   /// param1 Lineaire : Pente			Parabolique : Abscisse de l'extremum		Sinusoidale : Pente
	float param2_;   /// param2 Lineaire : Sens (1/-1)		Parabolique : Ordonn�e de l'extremum		Sinusoidale : P�riode (spatiale)
	float param3_;   /// param3 Lineaire : Inutilis�		Parabolique : Sens (1/-1)					Sinusoidale : Amplitude
	float param4_;   /// param4 Lineaire : Inutilis�		Parabolique : Inutilis�						Sinusoidale : Sens (1/-1)
	Trajectoire trajectoire_; /// Trajectoire du vaisseau
	float t_; /// Temps �coul� depuis la cr�ation
};

#endif //VAISSEAU_ECRAIREUR_H