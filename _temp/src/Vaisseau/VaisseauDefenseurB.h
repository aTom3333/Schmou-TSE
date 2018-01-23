#ifndef VAISSEAU_DEFENSEURB_H
#define VAISSEAU_DEFENSEURB_H

#include "Vaisseau.h"

/**
* @class VaisseauDefenseurB
* @brief classe du bouclier du VaisseauDefenseur
*
* Bouclier : Module d'un vaisseau ennemi
* Comportement : Pas de d�placement Pas de tir
*/

class VaisseauDefenseurB : public Vaisseau
{
	public:
		/**
		* @fn VaisseauDefenseurB
		* @brief Contructeur
		* @param x Abscisse de la position de d�part
		* @param y Ordonn�e de la position de d�part
		* @param createur Createur du module
		* Initialise le vaisseau � position et � la trajectoires d�sir�es
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
		* Indique au cr�ateur que l'annexe est d�tuite
		*/
		void destruction();
	private:

};


#endif // VAISSEAU_DEFENSEURB_H