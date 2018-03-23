#ifndef VAISSEAU_ATTAQUANT_H
#define VAISSEAU_ATTAQUANT_H

#include "../constantes.h"
#include "Vaisseau.h"
#include "../Capacites/CapMissile.h"
#include "../Utilitaires/Trajectoire.h"

/**
* @class VaisseauAttaquant
* @brief classe d'un ennemi de base : l'attaquant
*
* Attaquant : Vaisseau ennemi
* Comportement : Déplacement (Linéaire, Parabolique, Sinsoidale) uniquement
				 Tir de missile (ProjMissile)
*/

class VaisseauAttaquant : public Vaisseau
{
public: 
		/**
		* @fn VaisseauEclaireur
		* @brief Contructeur
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
		VaisseauAttaquant(float x, float y, Trajectoire traj, float param1, float param2, float param3 = 0, float param4 = 0);
		/**
		* @fn ~VaisseauEclaireur
		* @brief Destructeur
		*
		* Vide
		*/
		~VaisseauAttaquant();
		/**
		* @fn gestion
		* @brief Gère le comportement du vaisseau
		* @param window Fenetre SFML où le vaisseau sera affiché
		* @param tempsEcoule Temps écoulé depuis le dernier appel
		* @param input Classe Input donnant accés aux entrée
		*
		* Gère le déplacement et l'affichage du vaisseau
		*/
		void gestion(sf::RenderWindow & window, sf::Time tempsEcoule, Input& input) override;
		/**
		* @fn destruction
		* @brief Procedure a effectuer lorsque le vaisseau est détruit
		*
		* Détruit l'entité
		*/
		void destruction() { detruit_ = true; }

	private:
		sf::Vector2f posInit_; ///position de départ
		std::vector<float> params_; ///vecteur des paramètres, voir dans @c VaisseauEclaireur
									// param1 Lineaire : Sens			Parabolique : Sens							Sinusoidale : Sens (1/-1)
									// param2 Lineaire : Pente			Parabolique : Ordonnée de l'extremum		Sinusoidale : Période (spatiale)
									// param3 Lineaire : Inutilisé		Parabolique : Abscisse de l'extremum		Sinusoidale : Amplitude
									// param4 Lineaire : Inutilisé		Parabolique : Inutilisé						Sinusoidale : Pente
		Trajectoire trajectoire_; /// Trajectoire du vaisseau
		float t_; /// Temps écoulé depuis la création (temps de vie)
		int frames_;/// temps de vie dans une trajectoire
};


#endif // VAISSEAU_ATTAQUANT_H