#ifndef ENTITE_H
#define ENTITE_H

#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>


/**
 * @class Entite
 * @brief Classe virtuelle qui définit une entité
 *
 * Cette classe est une base à toutes les entités du jeu, les vaisseaux et les projectiles.
 * Elle définit l'interface globale à travers laquelle ces entités peuvent être manipulées
 */
class Entite
{
	friend bool collision(const Entite& e1, const Entite& e2);

	public:
		virtual ~Entite();
		const std::vector<sf::Shape*>& getForme() const { return forme_; }
		void afficher(sf::RenderWindow &window);

		// Tranformation setters & getters
        /**
         * @fn move
         * @brief Déplace l'entité en fonction de @a delta
         *
         * Appelle la fonction move de la SFML sur les attributs de l'objet appelant.
         * @param [in] delta un @c sf::Vector2f qui donne le déplacement en x et en y
         */
		void move(const sf::Vector2f& delta);
        /**
         * @fn setPosition
         * @brief Fixe la position de l'entité
         *
         * Cette fonction change la position de l'entité appelante avec les coordonnées
         * données en paramètres. Ces coordonnées sont relatives au coin supérieur gauche de la fenêtre.
         * Cette fonction est implémentée à partir de la fonction @a move afin que chaque élément reste
         * au même endroit par rapport aux autres
         * @param [in] pos Un @c sf::Vector2f qui contient la nouvelle position
         */
		void setPosition(const sf::Vector2f &pos);
        /**
         * @fn getPosition
         * @brief Renvoie la position de l'entité appelante
         *
         * Cette fonction renvoie la position actuelle de l'entité appelante par rapport au point
         * haut gauche de la fenêtre
         * @return la position de l'entité appelante
         */
		const sf::Vector2f& getPosition() const; 
		bool estDehors();

        /**
         * @fn rotate
         * @brief Tourne l'entité de l'angle passé en paramètre
         *
         * Cette fonction permet de aire tourner l'entité de l'angle passé en paramètre,
         * chaque élément composant l'entité est tourné. L'angle est donné en degrés
         * @param [in] angle
         */
		void rotate(float angle);
		void setRotation(float angle);
		float getRotation() const;

		void scale(float factor);
		void setScale(float factor);
		float getScale() const;

		void changeSpeed(int val); 

	protected:
		bool collisionable_ = true; /// <booléen vrai si collisionnable
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
