#ifndef DIVERS_H
#define DIVERS_H

#include <SFML/Graphics.hpp>

template<typename T,typename U>
bool est(const T& X)
{
	if (!std::is_base_of<U, T>())
		return false;
	return (dynamic_cast<U*>(&X) != nullptr);
}


void adapt_viewport(sf::RenderWindow& window);

#endif // !DIVERS_H
