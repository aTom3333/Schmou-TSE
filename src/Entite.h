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

		// Tranformation setters & getters
		void move(const sf::Vector2f& delta);
		void setPosition(const sf::Vector2f &pos);
		const sf::Vector2f& getPosition() const;
		bool estDehors();

		void rotate(float angle);
		void setRotation(float angle);
		float getRotation() const;

		void scale(float factor);
		void setScale(float factor);
		float getScale() const;

		void changeSpeed(int val);

	protected:
		bool collisionable_ = true; ///booléen vrai si collisionnable
		int equipe_; ///numéro d'équipe
		sf::Vector2f position_;
		float angle_;
		float scale_;
		sf::CircleShape cercleEnglobant_;
		std::vector<sf::Shape*> forme_;
		sf::Texture texture_;
		sf::Sprite sprite_;
		int vit_; /// < Vitesse actuelle
};

#endif // ENTITE_H
