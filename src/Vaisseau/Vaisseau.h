#ifndef VAISSEAU_H
#define VAISSEAU_H

#include <vector>
#include <string>
#include <algorithm>
#include "../Capacites/Capacite.h"
#include "../Entite.h"
#include "../Projectiles/Projectile.h"
#include "../Interface/Input.h"
#include "../def_type.h"



/**
 * @class Vaisseau
 * @brief classe du vaisseau (véhicule) d'un joueur ou d'un ennemi
 *
 * Description détaillée 
 */

class Vaisseau : public Entite
{
protected:
	//caractéristiques générales

	// personnalisation
	std::string nom_; /// < Nom du vaisseau
	int Nskin_; /// numéro du skin du vaisseau
	
	//Stats
	float atqM_ = 0;
	float defM_ = 0;

	float atq = 0;
	float def = 0;

	// liste de capacités
	std::vector<Capacite*> capacites_; /// Liste des capacités du vaisseau

    //section
	vaisseau_container annexes_; /// Vecteur contenant toute les parties annexes d'un vaisseau
	std::vector<bool> annexesB_; /// Vecteur indiquant si l'annexe au même indice existe encore
	Vaisseau * createur_; /// Si c'est une annexe, pointe vers le vaisseau  qui possede cette annexe. null_ptr sinon
	int nbModule_; /// Si c'est une annexe, indice dans le vecteur annexe du créateur

public:
	//structeurs
		Vaisseau();
        ~Vaisseau() override;
		/**
		* @fn gestion
		* @brief Gère le comportement du vaisseau
		* @param window Fenetre SFML où le vaisseau sera affiché
		* @param input Classe Input donnant accés aux entrée 
		*
		* Fonction virtuelle qui gère le comportement du vaisseau
		*/
		virtual void gestion(sf::RenderWindow& window, sf::Time tempsEcoule, Input& input) = 0;
		void gestionCapacite(proj_container &projectiles, sf::Time t_ecoule);
		/**
		* @fn agit
		* @brief Procédure lorsque le projectile agit avec une Entite
		* @param e Entite à modifier
		*
		* Vide
		*/
		void agit(Entite &e);
		/**
		* @fn destruction
		* @brief Procedure a effectuer lorsque le vaisseau est détruit
		*
		* Fonction virtuelle qui doit être surchargée pour les classes héritées.
		*/
		virtual void destruction() = 0; 

	//setters
		void setEquipe(Equipe equipe) {equipe_ = equipe; }
		void addCapacite(Capacite* skill) {capacites_.push_back(skill); }
		void setCapacite(Capacite* skill, int n){ capacites_[n] = skill; }
		void setnom(std::string nom){ nom_ = nom; }
		void setNskin(int Nskin){ Nskin_ = Nskin; }
		void setpvM(int pvM){ pvM_ = pvM; }
		void setActif(bool val){ actif_ = val; }
		void setAnnexeB(int ind, bool val){ annexesB_[ind] = val; }
		void setatqM(int atqM) { atqM_ = atqM; }
		void setdefM(int defM) { defM_ = defM; }
			

	//getters
		std::string getnom() const {return nom_; }
		int getNskin() const { return Nskin_; }
		int getpvM() const { return pvM_; }
		std::vector<Capacite*> getskills() const { return capacites_; }
		bool estActif() const { return actif_; }
		vaisseau_container getAnnexes() const { return annexes_; }
		std::vector<bool> getAnnexesB() const { return annexesB_; }
		int getatqM() const { return atqM_; }
		int getdefM() const { return defM_; }

};

#endif // VAISSEAU_H
