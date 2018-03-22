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
	Ecran();
	virtual ~Ecran() = default;

protected:
	std::stack<std::unique_ptr<Ecran>> pile_;
	std::vector<sf::Font> polices_;

};

#endif // !ECRAN_H
