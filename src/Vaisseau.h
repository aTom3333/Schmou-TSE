#ifndef VAISSEAU_H
#define VAISSEAU_H

#include <vector>
#include <string>
#include <algorithm>
#include "Capacite.h"
#include "Entite.h"
#include "Projectile.h"


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
			~Vaisseau();

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
			int defM_; /// < Défense de base
			int vitM_; /// < Vitesse de base
		// stats actualisées en jeu
			int pv_; /// < Points de vie actuels
			int atq_; /// < Attaque actuelle
			int def_; /// < Défense actuelle
			//int vit_; /// < Vitesse actuelle
		// liste de capacités
			std::vector<Capacite*> skills_; /// < Liste des capacités du vaisseau
};

#endif // VAISSEAU_H
