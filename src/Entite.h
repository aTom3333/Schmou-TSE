#ifndef ENTITE_H
#define ENTITE_H

#include "constantes.h"

#include <vector>
#include <memory>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <deque>

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
		void afficher(sf::RenderWindow &window, bool debug = false);

		// Tranformation setters & getters
        /**
         * @fn move
         * @brief Déplace l'Entite en fonction de @a delta
         *
         * Appelle la fonction move de la SFML sur les attributs de l'objet appelant.
         * @param [in] delta un @c sf::Vector2f qui donne le déplacement en x et en y
         */
		void move(sf::Vector2f& delta);
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
		/**
		* @fn setDetruit
		* @brief Fixe si l'entité est détruit ou non
		*
		* Fixe si l'entité est détruit ou non
		* @param bool L'etat à appliquer
		*/
		void setDetruit(bool val);
		/**
		* @fn estDetruit
		* @brief Renvoie un booléen indiquant si l'entité est détuit
		*
		* Renvoie un booléen indiquant si l'entité est détuit
		* Si l'entité n'a plus de point de vie, detruit_ est fixé à vrai
		*/
		bool estDetruit();
		/**
		* @fn agit
		* @brief Réalise l'action que l'@c Entite doit faire sur le vaisseau
		*
		* Fonction virtuelle qui doit être surchargée pour les classes héritées.
		* Elle réalise l'action que l'@c Entite appelant sur l'@c Entite passé en paramètre (dégats, changement de stat, ...)
		* @param e Une @c Entite sur lequel l'action de l'@c Entite va se faire
		*/
		virtual void agit(Entite& e) = 0;
		/**
		* @fn regen
		* @brief Redonne des points de vie, de l'armure et du bouclier toute les 100 ms
		* @param t Temps écoulé depuis le dernier appel
		*
		* Redonne des points de vie, de l'armure et du bouclier toute les 100 ms selons les paramètres de l'entité
		*/
		void regen(sf::Time t);
		/**
		* @fn recoitDegats
		* @brief Inflige des dégats au bouclier, à l'armure et aux points de vie en fonctions des dégats reçu
		*
		* Retire d'abord des points de bouclier. Si le bouclier est détuit, retire des points d'armure. 
		* Les dégats sur l'armure sont réduit. Retire le reste des points restant aux points de vie.
		*/
		void recoitDegats(float degats);
		float getDegats();
		/**
		* @fn destruction
		* @brief Procedure a effectuer lorsque le vaisseau est détruit
		*
		* Fonction virtuelle qui doit être surchargée pour les classes héritées.
		*/
		virtual void destruction() = 0;

		

		//getters
		Equipe getEquipe() const { return equipe_; };
		sf::Vector2f getTaille() const { return { sprite_.getGlobalBounds().width, sprite_.getGlobalBounds().height }; }//largeur, hauteur
		bool getInnate_() const { return innate_; }
		float getPVMax() { return pvMax_; };
		float getArmureMax() { return armureMax_; };
		float getBouclierMax() { return bouclierMax_; };
		float getPV() { return pv_; };
		float getArmure() { return armure_; };
		float getBouclier() { return bouclier_; };
		sf::Texture getTexture() { return texture_; };
		bool isInvincible() const { return framesInvincibilite_ != 0; };
		bool isCollisionneuse() { return collisionneuse_; }
		bool isCollisionnable() { return collisionable_; }

		//setters
		void setequipe_(Equipe equipe) { equipe_ = equipe; }
		void setInnate_(bool isInnate) { innate_ = isInnate; }
		void setNbPositions(int val);
		void setSmokeTexture(sf::Texture &text, sf::Color couleur = { 255,255,255 });

	protected:
		//coordonnées
		sf::Vector2f position_; ///< Position actuelle de l'Entite
		std::deque<sf::Vector2f> positionsPrev_; ///< Positions précédentes
			// /!\ne pas itérer, pas stocké contigument
		int nbPositions_ = 0; ///nombre de positions précédentes à conserver
		double angle_; ///< Orientation actuelle de l'Entite
		double scale_; ///< Échelle actuelle de l'Entite

		//caractéristiques
		bool collisionable_ = true; ///< Booléen vrai si l'Entite est collisionnable
		bool collisionneuse_ = true;
		Equipe equipe_; ///< Identifiant de l'équipe de l'Entite
		bool innate_ = false; ///false si doit rester dans l'écran

		//état
		bool detruit_ = false; /// ture lorsque que le vaisseau est détruit
		bool actif_; /// Booleen indiquant si la trajectoire a été amorcée

		//graphismes
		sf::CircleShape cercleEnglobant_; ///< Cercle Englobant de l'Entite
		std::vector<std::unique_ptr<sf::Shape>> forme_; ///< Forme de l'Entite
		sf::Texture texture_; ///< Texture du sprite de l'Entite
		sf::Texture textSmoke_; /// Texture à afficher sur la trainée du vaisseau
		sf::Sprite smoke_; /// Sprite à afficher sur la trainée du vaisseau
		sf::Sprite sprite_; ///< Sprite de l'Entite
		

		//son
		sf::SoundBuffer soundbuffer_;
		sf::Sound sound_;

		// Stats
		float pvMax_ = 0; /// Point de vie maximum de l'entite
		float armureMax_ = 0;  /// Armure maximum de l'entite
		float bouclierMax_ = 0;  /// Bouclier maximum de l'entite
		float vitM_ = 0; ///Vitesse maximale de l'entite

		float pv_ = pvMax_; /// Points de vie actuel
		float armure_ = armureMax_; ///Armure actuel
		float bouclier_ = bouclierMax_; /// Bouclier actuel
		float vit_ = vitM_; /// Vitesse actuelle de l'Entite

		float regenPV_ = 0; /// Points de vie rendu tout les 250 ms
		float regenARM_ = 0; /// Armure rendu tout les 250 ms
		float regenBOU_ = 0; /// Bouclier rendu tout les 250 ms
		float t_regen_; /// Temps écoulé depuis la dernière régénération

		float degats_ = 0; /// Dégats infligé en cas de de collision
		int framesInvincibilite_ = 0; /// Frames invincibilites
};

#endif // ENTITE_H
