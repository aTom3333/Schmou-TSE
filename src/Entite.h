#ifndef ENTITE_H
#define ENTITE_H

#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>


class Entite
{
	public:
		const std::vector<sf::Shape*>& getForme() const { return forme_; }

	//private:
		sf::Vector2f position_;
		double angle_;
		sf::CircleShape cercleEnglobant_;
		std::vector<sf::Shape*> forme_;
};

#endif // ENTITE_H
