#ifndef VAGUE_H
#define VAGUE_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Vaisseau/Vaisseau.h"
#include "Vaisseau/_vaisseaux.h"

typedef struct
{
	float t;
	Vaisseau *v;
	bool active;
} ElementVague;

/**
* @class Vague
* @brief Classe qui d�crit les vagues d'ennemis
*
* Cette classe pertmet de cr�er des vaisseaux selon un sch�ma d�fini, � partir d'un temps donn�
*/


class Vague
{
public:
	Vague();
	Vague(float t);
	~Vague();

	/**
	* @fn ajouterVaissseau
	* @brief Ajoute un vaisseau � la vague
	* @param t Le temps �coul� depuis le d�but de la vague avant apparition que le vaisseau apparaisse
	* @param v Le vaisseau � vaire apparaitre
	*/
	void ajouterVaisseau(float t, Vaisseau *v);
	/**
	* @fn gestion
	* @brief Gere la vague
	* @param t Temps �coul� depuis le d�but de la boucle
	* @param vaisseaux Vecteur de tous les vaisseaux pr�sent � l'�cran
	* Gere le d�clanchement de la vague et l'apparition des vaisseaux
	*/
	void gestion(std::vector<Vaisseau*> &vaisseaux, sf::Time t);
	/**
	* @fn setTempsDebut
	* @brief Gere la vague
	* @param t Temps de d�part de la vague
	* Fixe le temps de d�part du d�but de la vague
	*/
	void setTempsDebut(float t);
private:
	float t_debut_; /// Temps en millisecondes du d�but de la vague
	float t_; /// Temps depuis le d�but de la vague
	std::vector <ElementVague> v_; /// Vecteur des vaisseaux qui apparaissent
};

#endif //VAGUE_H