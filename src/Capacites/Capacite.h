#ifndef CAPACITE_H
#define CAPACITE_H

#include <vector>
#include <string>
#include <algorithm>
#include "../Projectiles/Projectile.h"
#include "../Entite.h"


/**
 * @class Capacite
 * @brief Classe abstraite qui définit la structure générale d'une capacité, à faire hériter de chaque capacité
 *
 * Cette classe abstraite permet de définir la structure générale d'une capacité du jeu,
 * elle doit être héritée pour chaque capacité qui est ajoutée au jeu
 */
class Capacite
{
	public:
		/**
		* @fn Capacite::Capacite
		* @brief Constructeur
		*
		* Vide
		*/
		Capacite() = default;
		/**
		* @fn Capacite::~Capacite
		* @brief Destructeur
		*
		* Vide
		*/
		virtual ~Capacite() = default;
		/**
		* @fn utiliser
		* @brief Fonction virtuel qui active la capacite lorsqu'elle est appelée
		* @param x Abscisse de la postion où la capacite est utilisée
		* @param y Ordonnée de la postion où la capacite est utilisée
		*
		* Fonction virtuel qui initialise la postion de départ et le timer
		*/
		virtual void utiliser(int x, int y) = 0;
		/**
		* @fn actualiser
		* @brief Fonction virtuel qui active les effets de la capacité
		* @param projectile Vecteur de tout les projectiles présent à l'écran
		* @param vaisseau Vaisseau qui a activé la compétance
		*
		* Fonction virtuel qui gère la création de projectiles et des modifications à apporter au vaisseau
		*/
		virtual void actualiser(std::vector<Projectile*> &projectiles, Entite *vaisseau) = 0;
		
		// Getters
		int const getCooldown() { return cooldown_; };
		int const getTime() { return t_; };
		std::string const getNom() { return nom_; };
	protected:
		int debutX_, debutY_; /// Position de départ
		int cooldown_; /// Nombre de frame à attendre avant de pouvoir utiliser la capacité à nouveau
		int t_; /// Temps écoulé depuis la dernière activation de la compétance
		std::string nom_; /// Nom de la compétance

};

#endif // CAPACITE_H
