#ifndef UTILITIES_H
#define UTILITIES_H
#include <SFML/Graphics/RenderWindow.hpp>
#include "../Entite.h"

/**
 * @brief Génère un entier aléatoire entre 0 et std::numeric_limits<long>::max()
 * @return un entier aléatoire
 */
int random();

/**
 * @brief Génère un entier aléatoire entre 0 et max inclus
 * @param max le maximum
 * @return un entier aléatoire
 */
int random(int max);

/**
 * @brief Génère un entier aléatoire entre min et max inclus
 * @param min le minimum
 * @param max le maximum
 * @return un entier aléatoire
 */
int random(int min, int max);

//test pour comparer des types
template<typename T, typename U>
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
* @brief Renvoie la distance entre l'origine et le point le plus éloigné de la forme
* @param forme Vector de unique_ptr utilisé dans Entite
* @param origine Origine du lanceur qui veut se faire englober
*/
double rayon_englobeur(const std::vector<std::unique_ptr<sf::Shape>> & forme, sf::Vector2f origine);

/**
* @brief Règle le cercle englobant de l'Entite en paramètre
* @param entite Entite qui doit se faire englober
*/
void englobeur_circulaire(Entite& entite);


#endif
