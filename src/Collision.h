#ifndef COLLISION_H
#define COLLISION_H

#include <SFML/Graphics.hpp>


bool collision(const sf::Shape& s1, const sf::Shape& s2);
bool collision(const sf::CircleShape& c1, const sf::CircleShape& c2);
bool collision(const sf::CircleShape& c, const sf::RectangleShape& r);
bool collision(const sf::RectangleShape& r, const sf::CircleShape& c);
bool collision(const sf::CircleShape& c, const sf::ConvexShape& co);
bool collision(const sf::ConvexShape& co, const sf::CircleShape& c);
bool collision(const sf::RectangleShape& r1, const sf::RectangleShape& r2);
bool collision(const sf::RectangleShape& r, const sf::ConvexShape& co);
bool collision(const sf::ConvexShape& co, const sf::RectangleShape& r);
bool collision(const sf::ConvexShape& co1, const sf::ConvexShape& co2);

#endif // COLLISION_H
