#ifndef DIVERS_H
#define DIVERS_H

#include "../Entite.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>

//test pour comparer des types
template<typename T,typename U>
bool est(const T& X)
{
	if (!std::is_base_of<U, T>())
		return false;
	return (dynamic_cast<U*>(&X) != nullptr);
}

//utilisé pour l'augmentation de la taille d'écran
void adapt_viewport(sf::RenderWindow& window);

//pour le chargeur
std::string trim(std::string str);
std::pair<std::string, std::string> tokenize(const std::string& str, char sep);

/**
*@fn rayon_englobeur
*@brief Renvoie la distance entre l'origine et le point le plus éloigné de la forme
*@param forme Vector de unique_ptr utilisé dans Entite
*@param orgine Origine du lanceur qui veut se faire englober
*/
double rayon_englobeur(const std::vector<std::unique_ptr<sf::Shape>> & forme, sf::Vector2f origine);

/**
*@fn englobeur_circulaire
*@brief Règle le cercle englobant de l'Entite en paramètre
@param entite Entite qui doit se faire englober
*/
void englobeur_circulaire(Entite& entite);


#endif // !DIVERS_H
