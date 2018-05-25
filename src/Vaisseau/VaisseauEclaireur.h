#ifndef VAISSEAU_ECRAIREUR_H
#define VAISSEAU_ECRAIREUR_H

#include <vector>
#include "Vaisseau.h"
#include "../Utilitaires/Trajectoire.h"

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
	* @param ecran Référence vers l'écran dans lequel est construit l'objet
	* @param x Abscisse de la position de départ
	* @param y Ordonnée de la position de départ
	* @param traj Trajectoire voulue (Linéaire, parabolique ou sinusoidale)
	* @param param1  Lineaire : Sens			Parabolique : Sens							Sinusoidale : Sens (1/-1)
	* @param param2  Lineaire : Pente			Parabolique : Ordonnée de l'extremum		Sinusoidale : Période (spatiale)
	* @param param3  Lineaire : Inutilisé		Parabolique : Abscisse de l'extremum		Sinusoidale : Amplitude
	* @param param4  Lineaire : Inutilisé		Parabolique : Inutilisé						Sinusoidale : Pente
	*
	* Initialise le vaisseau à position et à la trajectoires désirées
	* Equations si le vaisseau est en fonction du temps écoulé depuis la création:
		- Lineraire : 
			x = x0 + sens*v*t
			y = pente*(x - x0) + y0
		- Parabolique :
			x = x0 + sens*v*t (faux mais approximation si la parabole est assez large)
			y = (y0 - ordonnee)/(x0 - abscisse)^2 * (x - abscisse)^2 + ordonnee
		- Sinusoidale :
			x = x0 + sens*v*t (faux mais approximation si la différence de temps est très petite devant la période)
			y = pente * (x - x0) + y0 + amplitude * sin(2*pi/période * x)
	*/
	VaisseauEclaireur(Ecran &ecran, float x, float y, Trajectoire traj, double param1, double param2, double param3 = 0, double param4 = 0);
	/**
	* @fn ~VaisseauEclaireur
	* @brief Destructeurvide
	*/
	~VaisseauEclaireur() override = default;
	/**
	* @fn gestion
	* @brief Gère le comportement du vaisseau
	* @param proj_cont Vecteur de tous les projectiles à l'écran
	* @param input Classe Input donnant accés aux entrée
	*
	* Gère le déplacement et l'affichage du vaisseau
	*/
	void gestion(proj_container &proj_cont, Input& input) override;
	/**
	* @fn destruction
	* @brief Procedure a effectuer lorsque le vaisseau est détruit
	*
	* Détruit l'entité
	*/
	void destruction() override { detruit_ = true; }

private:
	sf::Vector2f posInit_; ///position de départ
	std::vector<float> params_; ///vecteur des paramètres, voir dans @c VaisseauEclaireur
	// param1 Lineaire : Sens			Parabolique : Sens							Sinusoidale : Sens (1/-1)
	// param2 Lineaire : Pente			Parabolique : Ordonnée de l'extremum		Sinusoidale : Période (spatiale)
	// param3 Lineaire : Inutilisé		Parabolique : Abscisse de l'extremum		Sinusoidale : Amplitude
	// param4 Lineaire : Inutilisé		Parabolique : Inutilisé						Sinusoidale : Pente
	Trajectoire trajectoire_; /// Trajectoire du vaisseau
	float t_; /// Temps écoulé depuis la création (temps de vie)
	size_t frames_;/// temps de vie dans une trajectoire
	
};

#endif //VAISSEAU_ECRAIREUR_H