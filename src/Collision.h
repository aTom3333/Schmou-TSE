#ifndef COLLISION_H
#define COLLISION_H

#include <SFML/Graphics.hpp>


bool collision(const sf::Shape& s1, const sf::Shape& s2);
bool collision_impl(const sf::Shape& s1, const sf::Shape& s2);
bool collision(const sf::CircleShape& c1, const sf::CircleShape& c2);
bool collision(const sf::CircleShape& c, const sf::Shape& co);
bool collision(const sf::Shape& co, const sf::CircleShape& c);

#endif // COLLISION_H
