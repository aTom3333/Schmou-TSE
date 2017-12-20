#ifndef ENTITE_H
#define ENTITE_H

#include <vector>
#include <memory>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "constantes.h"


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
        /**
         * @fn getForme
         * @brief Renvoie la forme de l'Entite
         *
         * Cette fonction renvoie la forme de l'Entite appelante. Cette forme se présente comme
         * un @c std::vector de pointeur (intelligents, des @c std::unique_ptr) vers des @c sf::Shape
         * car la forme totale de l'Entite est la juxtaposition de plusieurs formes plus simples représentées
         * par les @c sf::Shape indiviuelles
         * @return Un @c std::vector<std::unique_ptr<sf::Shape>> qui représente la forme de l'Entite
         */
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
		 * @brief Fixe l'échelle de L'entite
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

        /**
         * @fn estDehors
         * @brief Teste si l'Entite est hors d'une zone, par défaut l'écran
         *
         * Cette fonction permet de tester si l'Entite se trouve hors d'une zone rectangulaire délimitée
         * par x_min, y_min, x_max, y_max qui vallent par défaut les dimensions de l'écran. La détection
         * est grossière, le test est fait de savoir si le carré de côté deux fois le rayon du cercle englobant
         * est complétement compris hors de la zone à tester
         * @param [in] x_min L'abscisse minimale de la zone à tester, par défaut 0
         * @param [in] y_min L'ordonnée minimale de la zone à tester, par défaut 0
         * @param [in] x_max L'abscisse maximale de la zone à tester, par défaut la largeur de la fenêtre
         * @param [in] y_max L'ordonnée maximale de la zone à tester, par défaut la hauteur de la fenêtre
         * @return Un @c bool qui vaut @a true si l'Entite se trouve hors de la zone à tester et @a false sinon
         */
        bool estDehors(float x_min = 0, float y_min = 0, float x_max = ECRAN_L, float y_max = ECRAN_H) const;
        /**
         * @fn estDedans
         * @brief Teste si l'Entite est dans une zone, par défaut l'écran
         *
         * Cette fonction permet de tester si l'Entite se trouve dans une zone rectangulaire délimitée
         * par x_min, y_min, x_max, y_max qui vallent par défaut les dimensions de l'écran. La détection
         * est grossière, le test est fait de savoir si le carré de côté deux fois le rayon du cercle englobant
         * est complétement compris dans la zone à tester
         * @param [in] x_min L'abscisse minimale de la zone à tester, par défaut 0
         * @param [in] y_min L'ordonnée minimale de la zone à tester, par défaut 0
         * @param [in] x_max L'abscisse maximale de la zone à tester, par défaut la largeur de la fenêtre
         * @param [in] y_max L'ordonnée maximale de la zone à tester, par défaut la hauteur de la fenêtre
         * @return Un @c bool qui vaut @a true si l'Entite se trouve dans la zone à tester et @a false sinon
         */
        bool estDedans(float x_min = 0, float y_min = 0, float x_max = ECRAN_L, float y_max = ECRAN_H) const;

        /**
         * @fn changeSpeed
         * @brief Change la vitesse de l'Entite en ajoutant à la vitesse actuelle une certaine valeur
         *
         * Cette fonction permet de modifier la vitesse de l'Entite appelante en ajoutant à la vitesse actuelle
         * la valeur passée en paramètre. Cette dernière peut être négative pour diminuer la vitesse. La vitesse
         * ésultante peut également être négative, cela résultera en un mouvement en miroir
         * @param [in] val La valeur à ajouter à la vitesse actuelle
         */
		void changeSpeed(int val); 

	protected:
		bool collisionable_ = true; ///< Booléen vrai si l'Entite est collisionnable
		int equipe_; ///< Identifiant de l'équipe de l'Entite
		sf::Vector2f position_; ///< Position actuelle de l'Entite
		float angle_; ///< Orientation actuelle de l'Entite
		float scale_; ///< Échelle actuelle de l'Entite
		sf::CircleShape cercleEnglobant_; ///< Cercle Englobant de l'Entite
		std::vector<std::unique_ptr<sf::Shape>> forme_; ///< Forme de l'Entite
		sf::Texture texture_; ///< Texture du sprite de l'Entite
		sf::Sprite sprite_; ///< Sprite de l'Entite
		int vit_; ///< Vitesse actuelle de l'Entite
};

#endif // ENTITE_H
