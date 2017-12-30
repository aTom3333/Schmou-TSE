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
* Comportement : D�placement (Lin�aire, Parabolique, Sinsoidale) uniquement
				 Tir de missile (ProjMissile)
*/

class VaisseauAttaquant : public Vaisseau
{
public: 
		/**
		* @fn VaisseauEclaireur
		* @brief Contructeur
		* @param x Abscisse de la position de d�part
		* @param y Ordonn�e de la position de d�part
		* @param traj Trajectoire voulue (Lin�aire, parabolique ou sinusoidale)
		* @param param1  Lineaire : Sens			Parabolique : Sens							Sinusoidale : Sens (1/-1)
		* @param param2  Lineaire : Pente			Parabolique : Ordonn�e de l'extremum		Sinusoidale : P�riode (spatiale)
		* @param param3  Lineaire : Inutilis�		Parabolique : Abscisse de l'extremum		Sinusoidale : Amplitude
		* @param param4  Lineaire : Inutilis�		Parabolique : Inutilis�						Sinusoidale : Pente
		*
		* Initialise le vaisseau � position et � la trajectoires d�sir�es
		* Equations si le vaisseau est en fonction du temps �coul� depuis la cr�ation:
		- Lineraire :
		x = x0 + sens*v*t
		y = pente*(x - x0) + y0
		- Parabolique :
		x = x0 + sens*v*t (faux mais approximation si la parabole est assez large)
		y = (y0 - ordonnee)/(x0 - abscisse)^2 * (x - abscisse)^2 + ordonnee
		- Sinusoidale :
		x = x0 + sens*v*t (faux mais approximation si la diff�rence de temps est tr�s petite devant la p�riode)
		y = pente * (x - x0) + y0 + amplitude * sin(2*pi/p�riode * x)
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
		* @brief G�re le comportement du vaisseau
		* @param window Fenetre SFML o� le vaisseau sera affich�
		* @param tempsEcoule Temps �coul� depuis le dernier appel
		* @param input Classe Input donnant acc�s aux entr�e
		*
		* G�re le d�placement et l'affichage du vaisseau
		*/
		void gestion(sf::RenderWindow & window, sf::Time tempsEcoule, Input input);
		/**
		* @fn destruction
		* @brief Procedure a effectuer lorsque le vaisseau est d�truit
		*
		* D�truit l'entit�
		*/
		void destruction() { detruit_ = true; }

	private:
		sf::Vector2f posInit_; ///position de d�part
		std::vector<float> params_; ///vecteur des param�tres, voir dans @c VaisseauEclaireur
									// param1 Lineaire : Sens			Parabolique : Sens							Sinusoidale : Sens (1/-1)
									// param2 Lineaire : Pente			Parabolique : Ordonn�e de l'extremum		Sinusoidale : P�riode (spatiale)
									// param3 Lineaire : Inutilis�		Parabolique : Abscisse de l'extremum		Sinusoidale : Amplitude
									// param4 Lineaire : Inutilis�		Parabolique : Inutilis�						Sinusoidale : Pente
		Trajectoire trajectoire_; /// Trajectoire du vaisseau
		float t_; /// Temps �coul� depuis la cr�ation (temps de vie)
		int frames_;/// temps de vie dans une trajectoire
};


#endif // VAISSEAU_ATTAQUANT_H