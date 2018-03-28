#ifndef PROJ_BISMILLAH_H
#define PROJ_BISMILLAH_H

#include "Projectile.h"

class ProjBismillah : public Projectile
{
	public:
		/**
		* @fn ProjBismillah
		* @brief Constructeur
		* @param x Abscisse de la position de départ du projectile
		* @param y Ordonnée de la position de départ du projectile
		* @param equipe Représente l'équipe depuis _constante.h : enum Equipe
		* @param sound Son par défaut donné par la capacité qui crée le proj
		*
		* Créer un projectile piou à la position donnée en paramètre
		*/
		ProjBismillah(Ecran& ecran, std::shared_ptr<Entite> lanceur, std::vector<sf::Sprite>& sprite, std::vector<sf::Sound>& sound, Equipe equipe);
		/**
		* @fn ~ProjBismillah
		* @brief Destructeur
		*
		* Vide
		*/
		~ProjBismillah() override = default;
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

	private:
		const float largeur_max_;
		sf::Clock t_age_;

};



#endif // !PROJ_BISMILLAH_H

