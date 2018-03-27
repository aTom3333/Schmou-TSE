#ifndef PROJ_PIOU_H
#define PROJ_PIOU_H

#include "Projectile.h"

/**
* @class ProjPiou
* @brief Projectile de test
*
* Projectile de base. Tire en ligne droite (vers le haut)
*/

//TODO refaire la doc


class ProjPiou : public Projectile
{
	public:
		/**
		* @fn ProjPiou
		* @brief Constructeur
		* @param x Abscisse de la position de départ du projectile
		* @param y Ordonnée de la position de départ du projectile
		* @param equipe Représente l'équipe depuis _constante.h : enum Equipe
		* @param sound Son par défaut donné par la capacité qui crée le proj
		*
		* Créer un projectile piou à la position donnée en paramètre
		*/
		ProjPiou(Ecran& ecran, std::shared_ptr<Entite> lanceur, std::vector<sf::Sprite>& sprite, std::vector<sf::Sound>& sound, Equipe equipe = NEUTRE);
		/**
		* @fn ~ProjPiou
		* @brief Destructeur
		*
		* Vide
		*/
		~ProjPiou() override = default;
		/**
		* @fn gestion
		* @brief Gestion du projectile
		* @param window Fenetre de jeu
		*
		* Gestion du déplacement et de l'affichage
		*/
		void gestion() override;
		/**
		* @fn agit
		* @brief Procédure lorsque le projectile agit avec une Entite
		* @param e Entite à modifier
		*
		* Vide
		*/
		void agit(Entite &e) override;

};

#endif
