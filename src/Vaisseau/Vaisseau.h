#ifndef VAISSEAU_H
#define VAISSEAU_H

#include "../Capacites/Capacite.h"
#include "../Entite.h"
#include "../Projectiles/Projectile.h"
#include "../Interface/Input.h"
#include "../def_type.h"
#include "../Utilitaires/Divers.h"
#include <vector>
#include <string>
#include <algorithm>



/**
 * @class Vaisseau
 * @brief classe du vaisseau (véhicule) d'un joueur ou d'un ennemi
 *
 * Description détaillée 
 */

class Vaisseau : public Entite
{
	public:
		explicit Vaisseau(Ecran& ecran) : Entite(ecran) {};
		/**
		* @fn gestion
		* @brief Gère le comportement du vaisseau
		* @param window Fenetre SFML où le vaisseau sera affiché
		* @param input Classe Input donnant accés aux entrée 
		*
		* Fonction virtuelle qui gère le comportement du vaisseau
		*/
		virtual void gestion(proj_container &proj_cont, Input& input) = 0;
		void gestionCapacite(proj_container &projectiles);
		/**
		* @fn agit
		* @brief Procédure lorsque le projectile agit avec une Entite
		* @param e Entite à modifier
		*
		* Vide
		*/
		void agit(Entite &e) override;
		/**
		* @fn destruction
		* @brief Procedure a effectuer lorsque le vaisseau est détruit
		*
		* Fonction virtuelle qui doit être surchargée pour les classes héritées.
		*/
		void destruction() override = 0; 

		//setters
			void setEquipe(const Equipe equipe) {equipe_ = equipe; }
			void addCapacite(std::unique_ptr<Capacite> skill) {capacites_.push_back(std::move(skill)); }
			void addCapacite(Capacite* skill) { capacites_.emplace_back(skill);}
			void setCapacite(Capacite* skill, const size_t& n){ capacites_.at(n).reset(skill); }
			void setNom(const std::string& nom){ nom_ = nom; }
			void setNskin(const size_t Nskin){ Nskin_ = Nskin; }
			void setAtqM(const float atqM) { atqM_ = atqM; }
			void setDefM(const float defM) { defM_ = defM; }
			

		//getters
			std::string getNom() const {return nom_; }
			size_t getNskin() const { return Nskin_; }
			const std::vector<std::unique_ptr<Capacite>>& getskills() const { return capacites_; }
			bool estActif() const { return actif_; }
			vaisseau_container getAnnexes() const { return annexes_; }
			float getatqM() const { return atqM_; }
			float getdefM() const { return defM_; }

	protected:
		// Caractéristiques générales

		// Personnalisation
		std::string nom_; /// < Nom du vaisseau
		size_t Nskin_; /// numéro du skin du vaisseau

		// Stats
		float atqM_ = 0;
		float atq = 0;

		float defM_ = 0;
		float def = 0;

		// Liste de capacités
		std::vector<std::unique_ptr<Capacite>> capacites_; /// Liste des capacités du vaisseau

		// Composition de vaisseaux, composé d'annexes de classe Vaisseau
		vaisseau_container annexes_; /// Vecteur contenant toute les parties annexes d'un vaisseau


};

#endif // VAISSEAU_H
