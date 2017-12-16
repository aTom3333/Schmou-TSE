#ifndef ENTITE_H
#define ENTITE_H

#include <vector>
#include <memory>
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
	/**
	 * @fn collision
	 * @brief Détecte une collision entre deux Entite
	 *
	 * Cette fonction permet de détecter si deux Entite sont en collision ou non.
	 * Cette fonction prend en compte si les deux Entite sont collisionables, si elles sont d'équipes différentes,
	 * si leur cercles englobants sont en collision et finalement si leur formes de
	 * collisions sont en collision
	 * @param [in] e1 La première Entite à tester
	 * @param [in] e2 La deuxième Entite à tester
	 * @return Un @c bool qui vaut @a true si les Entite sont en collision et @a false sinon
	 */
	friend bool collision(const Entite& e1, const Entite& e2);

	public:
		/**
		 * @fn ~Entite
		 * @brief Destructeur par défaut
		 *
		 * Destructeur virtuel par défaut de la classe Entite. Le destructeur est virtuel
		 * car la classe a vocation à être héritée. Il n'y a rien de spécial à faire
		 * donc le destructeur par défaut convient
		 */
		virtual ~Entite() = default;
		const std::vector<std::unique_ptr<sf::Shape>>& getForme() const { return forme_; }
		/**
		 * @fn afficher
		 * @brief Affiche le sprite de l'Entite
		 *
		 * Appelle la fonction afficher de la SFML sur les attributs de l'objet appelant.
		 * Peut également afficher des informations de debug telles que le cercle englobant,
		 * et la forme de collision.
		 * @param [in,out] window Fenêtre SFML dans laquelle afficher l'entité.
		 * @param [in] debug Un @c bool qui vaut @a true si les informations de debug doivent être affichées et @a false sinon.
		 */
		void afficher(sf::RenderWindow &window, bool debug=false) const;

		// Tranformation setters & getters
        /**
         * @fn move
         * @brief Déplace l'Entite en fonction de @a delta
         *
         * Appelle la fonction move de la SFML sur les attributs de l'objet appelant.
         * @param [in] delta un @c sf::Vector2f qui donne le déplacement en x et en y
         */
		void move(const sf::Vector2f& delta);
        /**
         * @fn setPosition
         * @brief Fixe la position de l'Entite
         *
         * Cette fonction change la position de l'Entite appelante avec les coordonnées
         * données en paramètres. Ces coordonnées sont relatives au coin supérieur gauche de la fenêtre.
         * Cette fonction est implémentée à partir de la fonction @a move afin que chaque élément reste
         * au même endroit par rapport aux autres s'il n'ont pas la même position initiale.
         * @param [in] pos Un @c sf::Vector2f qui contient la nouvelle position
         */
		void setPosition(const sf::Vector2f &pos);
        /**
         * @fn getPosition
         * @brief Renvoie la position de l'Entite appelante
         *
         * Cette fonction renvoie la position actuelle de l'Entite appelante par rapport au point
         * haut gauche de la fenêtre
         * @return la position de l'entité appelante
         */
		const sf::Vector2f& getPosition() const;

        /**
         * @fn rotate
         * @brief Tourne l'Entite de l'angle passé en paramètre
         *
         * Cette fonction permet de aire tourner l'entité de l'angle passé en paramètre,
         * chaque élément composant l'entité est tourné. L'angle est donné en degrés
         * @param [in] angle
         */
		void rotate(float angle);
		/**
		 * @fn setRotation
		 * @brief Fixe l'orientation de l'Entite appelante
		 *
		 * Cette fonction change l'orientation de l'Entite appelante à l'angle passé en paramètres.
		 * La valeur de l'angle est donnée en degrés.
		 * Cette fonction est implémentée en utilisant la fonction rotate pour que les éléments
		 * ne soient pa décalés les uns par rapport aux autres s'ils ne disposent pas de la même orientation initiale.
		 * @param [in] angle La nouvelle orientation de l'Entite
		 */
		void setRotation(float angle);
		/**
		 * @fn getRotation
		 * @brief Récupère l'orientation de l'Entite
		 *
		 * Cette fonction renvoie l'orientation actuelle de l'Entite appelante.
		 * La valeur renvoyée correspond à un angle en degrés
		 * @return Un @c float qui correspond à l'eorientation de l'Entite
		 */
		float getRotation() const;

		/**
		 * @fn scale
		 * @brief Change l'échelle de l'Entite
		 *
		 * Cette fonction permet de modifier l'échelle de l'Entite appelante
		 * en appliquant un coefficient multiplicateur à ses dimensions. Un coefficient
		 * de 0.5 divisera les dimentions par 2, à l'inverse un coefficient de 2 rendra l'Entite
		 * 2 fois plus grande. Un coefficient de 1 ne changera rien.
		 * @param [in] factor Le coefficient multiplicateur d'échelle à appliquer
		 */
		void scale(float factor);
		/**
		 * @fn setScale
		 * @brief Fixer l'échelle de L'entite
		 *
		 * Cette fonction permet de fixer l'échelle de L'entite appelante.
		 * Contrairement à la fonction scale, cette fonction fixe l'échelle de manière absolue
		 * et non relativement au changements d'échelle déjà appliqué à l'Entite
		 * @param [in] factor Le facteur d'échelle à appliquer
		 */
		void setScale(float factor);
        /**
         * @fn getScale
         * @brief Renvoie l'échelle de l'Entite
         *
         * Cette fonction renvoie l'échelle actuelle de l'Entite appelante
         * @return Un @c float qui correspond au facteur d'échelle de l'Entite
         */
		float getScale() const;

        bool estDehors() const;

		void changeSpeed(int val); 

	protected:
		bool collisionable_ = true; ///< Booléen vrai si collisionnable
		int equipe_; ///< numéro d'équipe
		sf::Vector2f position_;
		float angle_;
		float scale_;
		sf::CircleShape cercleEnglobant_;
		std::vector<std::unique_ptr<sf::Shape>> forme_;
		sf::Texture texture_;
		sf::Sprite sprite_;
		int vit_; ///< Vitesse actuelle
};

#endif // ENTITE_H
