#ifndef ENTITE_H
#define ENTITE_H

#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>


class Entite
{
	friend bool collision(const Entite& e1, const Entite& e2);

	public:
		virtual ~Entite() = default;
		const std::vector<sf::Shape*>& getForme() const { return forme_; }
		void afficher(sf::RenderWindow &window);

	//private:
		bool collisionable_ = true;
		bool joueur_;
		sf::Vector2f position_;
		double angle_;
		sf::CircleShape cercleEnglobant_;
		std::vector<sf::Shape*> forme_;
		sf::Texture texture_;
		sf::Sprite sprite_;
};

#endif // ENTITE_H
