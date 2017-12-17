#ifndef VAISSEAU_ECRAIREUR_H
#define VAISSEAU_ECRAIREUR_H

#include "../constantes.h"
#include "Vaisseau.h"

/**
* @class VaisseauEclaireur
* @brief classe d'un ennemi de base : l'éclaireur
*
* Eclaireur : Vaisseau ennemi
* Comportement : Déplacement (Linéaire, Parabolique, Sinsoidale) uniquement : pas de tir
*/

class VaisseauEclaireur : public Vaisseau
{
public:
	/**
	* @fn VaisseauEclaireur
	* @brief Contructeur
	* @param x Abscisse de la position de départ
	* @param y Ordonnée de la position de départ
	* @param traj Trajectoire voulue (Linéaire, parabolique ou sinusoidale)
	* @param param1 Lineaire : Pente		Parabolique : Abscisse de l'extremum		Sinusoidale : Pente
	* @param param2 Lineaire : Sens (1/-1)	Parabolique : Ordonnée de l'extremum		Sinusoidale : Période spatiale
	* @param param3 Lineaire : Inutilisé	Parabolique : Sens (1/-1)					Sinusoidale : Amplitude
	* @param param4 Lineaire : Inutilisé	Parabolique : Inutilisé						Sinusoidale : Sens (1/-1)
	*
	* Initialise le vaisseau à position et à la trajectoires désirées
	* Equations si le vaisseau est en fonction du temps écoulé depuis la création:
		- Lineraire : 
			x = x0 + param2*v*t
			y = param1*(x - x0) + y0
		- Parabolique :
			x = x0 + param3*v*t (faux mais approximation si la parabole est assez large)
			y = (y0 - param2)/(x0 - param1)^2 * (x - param1)^2 + param2
		- Sinusoidale :
			x = x0 + param4*v*t (faux mais approximation si la différence de temps est très petite devant la période)
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
	* @brief Gère le comportement du vaisseau
	* @param window Fenetre SFML où le vaisseau sera affiché
	* @param tempsEcoule Temps écoulé depuis le dernier appel
	*
	* Gère le déplacement et l'affichage du vaisseau
	*/
	void gestion(sf::RenderWindow & window, float tempsEcoule);
private:
	float x0_; /// Abscisse de départ
	float y0_; /// Ordonnée de départ
	float param1_;   /// param1 Lineaire : Pente			Parabolique : Abscisse de l'extremum		Sinusoidale : Pente
	float param2_;   /// param2 Lineaire : Sens (1/-1)		Parabolique : Ordonnée de l'extremum		Sinusoidale : Période (spatiale)
	float param3_;   /// param3 Lineaire : Inutilisé		Parabolique : Sens (1/-1)					Sinusoidale : Amplitude
	float param4_;   /// param4 Lineaire : Inutilisé		Parabolique : Inutilisé						Sinusoidale : Sens (1/-1)
	Trajectoire trajectoire_; /// Trajectoire du vaisseau
	float t_; /// Temps écoulé depuis la création
};

#endif //VAISSEAU_ECRAIREUR_H