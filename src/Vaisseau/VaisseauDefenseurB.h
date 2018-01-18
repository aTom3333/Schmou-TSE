#ifndef VAISSEAU_DEFENSEURB_H
#define VAISSEAU_DEFENSEURB_H

#include "Vaisseau.h"

/**
* @class VaisseauDefenseurB
* @brief classe du bouclier du VaisseauDefenseur
*
* Bouclier : Module d'un vaisseau ennemi
* Comportement : Pas de déplacement Pas de tir
*/

class VaisseauDefenseurB : public Vaisseau
{
	public:
		/**
		* @fn VaisseauDefenseurB
		* @brief Contructeur
		* @param x Abscisse de la position de départ
		* @param y Ordonnée de la position de départ
		* @param createur Createur du module
		* Initialise le vaisseau à position et à la trajectoires désirées
		*/
		VaisseauDefenseurB(int nb, float x, float y, Vaisseau *createur);
		/**
		* @fn ~VaisseauEclaireur
		* @brief Destructeur
		*
		* Vide
		*/
		~VaisseauDefenseurB();
		/**
		* @fn gestion
		* @brief Gère le comportement du vaisseau
		* @param window Fenetre SFML où le vaisseau sera affiché
		* @param tempsEcoule Temps écoulé depuis le dernier appel
		* @param input Classe Input donnant accés aux entrée
		*
		* Gère le déplacement et l'affichage du vaisseau
		*/
		void gestion(sf::RenderWindow & window, sf::Time tempsEcoule, Input& input);
		/**
		* @fn destruction
		* @brief Procedure a effectuer lorsque le vaisseau est détruit
		*
		* Indique au créateur que l'annexe est détuite
		*/
		void destruction();
	private:

};


#endif // VAISSEAU_DEFENSEURB_H