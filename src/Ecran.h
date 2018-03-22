#ifndef CLASSE_ECRAN_H
#define CLASSE_ECRAN_H

#include <stack>
#include <memory>
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class Ecran
{
public:
	//structeurs
	Ecran(std::stack<std::unique_ptr<Ecran>>& pile); /// < constructeur principal
	virtual ~Ecran() = default;

	virtual void executer() = 0;

protected:
	std::stack<std::unique_ptr<Ecran>>& pile_; /// < pile de tous les écrans du jeu empilés
	std::vector<sf::Font> polices_;/// < vector de toutes les polices du jeu

};

#endif // !ECRAN_H
