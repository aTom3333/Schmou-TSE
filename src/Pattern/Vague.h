#ifndef VAGUE_H
#define VAGUE_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "../Vaisseau/_vaisseaux.h"
#include "../def_type.h"

struct VaisseauVague
{
	sf::Time t_depart_element;
	vaisseau_ptr vaiss;
	bool actif = false;
};
//TODO CL vague de Entités

/**
* @class Vague
* @brief Classe qui décrit les vagues d'ennemis
*
* Cette classe pertmet de créer des vaisseaux selon un schéma défini, à partir d'un temps donné
*/


class Vague
{
	public:
		/**
		*@fn Vague
		*@brief Constructeur
		*@param ecran Référence vers l'écran
		*@param t Temps de départ de la vague après la construction de la partie
		*/
		explicit Vague(Ecran& ecran, const sf::Time& t = sf::Time::Zero);
		~Vague() = default;

		/**
		* @fn ajouterElement
		* @brief Ajoute un élement à la vague
		* @param e L'élement à ajouter
		*/
		void ajouterElement(const VaisseauVague e) { vaisseaux_vague_.push_back(e); }
		/**
		* @fn gestion
		* @brief Gère la vague
		* @param vaisseaux Vecteur de tous les vaisseaux présent à l'écran
		* Gere le déclanchement de la vague et l'apparition des vaisseaux
		*/
		void gestion(vaisseau_container &vaisseaux);
		/**
		* @fn setTempsDepart
		* @brief Fixe le temps de départ de la vague
		* @param t Temps de départ de la vague
		* Fixe le temps de départ du début de la vague
		*/
		void setTempsDepart(sf::Time t) { t_depart_ = t; }

		// Itérateurs
		std::vector<VaisseauVague>::iterator begin() { return vaisseaux_vague_.begin(); }
		std::vector<VaisseauVague>::const_iterator begin() const { return vaisseaux_vague_.cbegin(); }
		std::vector<VaisseauVague>::iterator end() { return vaisseaux_vague_.end(); }
		std::vector<VaisseauVague>::const_iterator end() const { return vaisseaux_vague_.cend(); }

		//getters
		std::vector<VaisseauVague> getElements() const { return vaisseaux_vague_; }

		//setters
		void setEquipeAll(Equipe equipe) {
			for (auto& element : vaisseaux_vague_) element.vaiss->setEquipe(equipe); 
		}


	private:
		// Référence vers l'écran
		Ecran& ecran_;

		// Temps
		sf::Time t_depart_; ///<Temps de départ de la vague
		sf::Time t_depuis_debut_partie_; ///<Durée depuis la création de la partie

		std::vector<VaisseauVague> vaisseaux_vague_; ///<Vecteur des vaisseaux qui constituent le pattern
};

#endif //VAGUE_H