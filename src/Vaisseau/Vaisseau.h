#ifndef VAISSEAU_H
#define VAISSEAU_H

#include <vector>
#include <string>
#include <algorithm>
#include "../Capacites/Capacite.h"
#include "../Entite.h"
#include "../Projectiles/Projectile.h"
#include "../Interface/Input.h"


/**
 * @class Vaisseau
 * @brief classe du vaisseau (véhicule) d'un joueur ou d'un ennemi
 *
 * Description détaillée 
 */

class Vaisseau : public Entite
{
	public:
		//structeurs
			explicit Vaisseau();
            ~Vaisseau() override;
			/**
			* @fn gestion
			* @brief Gère le comportement du vaisseau
			* @param window Fenetre SFML où le vaisseau sera affiché
			* @param input Classe Input donnant accés aux entrée 
			*
			* Fonction virtuelle qui gère le comportement du vaisseau
			*/
			virtual void gestion(sf::RenderWindow & window, sf::Time tempsEcoule, Input input) = 0;
			void gestionCapacite(std::vector <Projectile*> &projectiles, sf::Time t_ecoule);
			/**
			* @fn agit
			* @brief Procédure lorsque le projectile agit avec une Entite
			* @param e Entite à modifier
			*
			* Vide
			*/
			void agit(Entite &e) {};

		//setters
			void setEquipe(int equipe); ///définit l'équipe (entier)
			void addCapacite(Capacite* skill); /// < ajoute la @c Capacité skill à la liste des capacités skills_ du vaisseau
			void setnom(std::string nom);
			void setNskin(int Nskin);
			void setpvM(int pvM);
			void setatqM(int atqM);
			void setdefM(int defM);
			void setvitM(int vitM);
			void setpv(int pv);
			void setatq(int atq);
			void setdef(int def);
			void setvit(int vit);

		//getters
			std::string getnom();
			int getNskin();
			int getpvM();
			int getatqM();
			int getdefM();
			int getvitM();
			int getpv();
			int getatq();
			int getdef();
			int getvit();
			std::vector<Capacite*> getskills();

	protected:
		//caractéristiques générales

		// personnalisation
			std::string nom_; /// < Nom du vaisseau
			int Nskin_; /// < numéro du skin du vaisseau

		// stats de base
			int pvM_; /// < Points de vie de base
			int atqM_; /// < Attaque de base
			int defM_; /// Défense de base
			int vitM_; /// Vitesse de base
		// stats actualisées en jeu
			int pv_; /// Points de vie actuels
			int atq_; /// Attaque actuelle
			int def_; /// Défense actuelle
			//int vit_; /// Vitesse actuelle
		// liste de capacités
			std::vector<Capacite*> capacites_; /// Liste des capacités du vaisseau
};

#endif // VAISSEAU_H
