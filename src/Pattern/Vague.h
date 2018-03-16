#ifndef VAGUE_H
#define VAGUE_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "../Vaisseau/_vaisseaux.h"
#include "../def_type.h"

typedef struct
{
	float t;
	vaisseau_ptr v;
	bool active;
} ElementVague;

/**
* @class Vague
* @brief Classe qui décrit les vagues d'ennemis
*
* Cette classe pertmet de créer des vaisseaux selon un schéma défini, à partir d'un temps donné
*/


class Vague
{
public:
	Vague();
	explicit Vague(float t);
	~Vague();

	/**
	* @fn ajouterVaissseau
	* @brief Ajoute un vaisseau à la vague
	* @param t Le temps écoulé depuis le début de la vague avant apparition que le vaisseau apparaisse
	* @param v Le vaisseau à vaire apparaitre
	*/
	void ajouterVaisseau(float t, vaisseau_ptr v);
	/**
	* @fn gestion
	* @brief Gere la vague
	* @param t Temps écoulé depuis le début de la boucle
	* @param vaisseaux Vecteur de tous les vaisseaux présent à l'écran
	* Gere le déclanchement de la vague et l'apparition des vaisseaux
	*/
	void gestion(vaisseau_container &vaisseaux, sf::Time t);
	/**
	* @fn setTempsDebut
	* @brief Gere la vague
	* @param t Temps de départ de la vague
	* Fixe le temps de départ du début de la vague
	*/
	void setTempsDebut(float t);

	//getters
	std::vector<ElementVague> getv_() { return v_; }

	//setters
	void setEquipeAll(Equipe equipe) {
		for (auto &element : v_) element.v->setequipe_(equipe); 
	}

private:
	float t_debut_; /// Temps en millisecondes du début de la vague
	float t_; /// Temps depuis le début de la vague
	std::vector<ElementVague> v_; /// Vecteur des vaisseaux qui apparaissent

};

#endif //VAGUE_H