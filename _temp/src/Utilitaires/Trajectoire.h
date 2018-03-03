#ifndef Trajectoire_H
#define Trajectoire_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <cmath>

/**
*@enum Trajectoire
*@brief liste �num�r�e des types possibles de trajectoire
*
*
*/
enum Trajectoire
{
	LINEAIRE,
	PARABOLIQUE,
	SINUS,
	MOUTON
};

/**
*@fn traj_position
*@brief cacule le point actuel dans la trajectoire donn�e
*
*@param trajectoire Nom de la trajectoire voulue (voir Trajectoire)
*@param t Temps actuel depuis la cr�ation de l'entit�
*@param vit_ vitesse de l'entit�
*@param posInit Position initiale
*@param params liste de float pour param�trer la forme des courbes
*
*/
sf::Vector2f traj_position(Trajectoire trajectoire,float t, float vit_, sf::Vector2f posInit, std::vector<float> params);


#endif // !Trajectoire_H
