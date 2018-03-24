#ifndef CAPACITE_H
#define CAPACITE_H

#include <vector>
#include <string>
#include <algorithm>
#include "../Projectiles/Projectile.h"
#include "../Entite.h"
#include "../def_type.h"


/**
 * @class Capacite
 * @brief Classe abstraite qui définit la structure générale d'une capacité, à faire hériter de chaque capacité
 *
 * Cette classe abstraite permet de définir la structure générale d'une capacité du jeu,
 * elle doit être héritée pour chaque capacité qui est ajoutée au jeu
 */
class Capacite
{
	public:
		/**
		* @fn Capacite::Capacite
		* @brief Constructeur
		*
		* Vide
		*/
		Capacite() = default;
		/**
		* @fn Capacite::~Capacite
		* @brief Destructeur
		*
		* Vide
		*/
		virtual ~Capacite() = default;
		/**
		* @fn utiliser
		* @brief Fonction virtuel qui active la capacite lorsqu'elle est appelée
		* @param x Abscisse de la position où la capacite est utilisée
		* @param y Ordonnée de la position où la capacite est utilisée
		*
		* Fonction virtuel qui initialise la position de départ et le timer
		*/
		virtual void utiliser(int x, int y) = 0;
		/**
		* @fn actualiser
		* @brief Fonction virtuel qui active les effets de la capacité
		* @param projectile Vecteur de tout les projectiles présent à l'écran
		* @param vaisseau Vaisseau qui a activé la compétence
		* @param tempEcoule Temps écoulé depuis la dernière boucle
		*
		* Fonction virtuel qui gère la création de projectiles et des modifications à apporter au vaisseau
		*/
		virtual void actualiser(proj_container &projectiles, Entite& vaisseau, float tempsEcoule) = 0;

		void initIcon(int i);
		
		// Getters
		float getCooldown() const { return cooldown_; };
		float getTime() const { return t_; };
		const std::string& getNom() const { return nom_; };
		const sf::Sprite& getIcon() const { return capacite_; };
		const sf::RectangleShape& getMasque() const { return masque_; };
		const sf::Text& getText() const { return text_; };
		bool getAffiche() { return affiche_; };
		bool getTir() { return tir_; };
		const sf::SoundBuffer& getSoundBuffer_() const { return soundbuffer_; }
		const sf::Sound& getSound_() const { return sound_; }



		void afficherNom(sf::RenderWindow &window) { window.draw(text_); };
		void gestionIcon();
		

	protected:
		sf::Texture capText_;
		sf::Sprite capacite_;
		sf::RectangleShape masque_;
		sf::Font font_;
		sf::Text text_;
		bool affiche_ = false;
		bool tir_ = false;
		std::string nom_; /// Nom de la compétence
		unsigned int niveau_; /// Niveau, à partir de 1

		double debutX_, debutY_; /// Position de départ
		float cooldown_; /// Temps à attendre avant de pouvoir utiliser la capacité à nouveau
		float t_stay; ///Temps après lequel le projectile issu disparait

		float t_; /// Temps écoulé depuis la dernière activation de la compétence
		unsigned int frames_; /// Nombre de frames écoulé depuis la dernière activation

		bool autoAim; ///état visée auto

		//Texture
		sf::Texture texture_; /// Texture en cas de texture unique
		sf::Sprite sprite_; /// Sprite en cas de sprite unique
		std::vector<std::shared_ptr<sf::Texture>> textureV_; ///< Vecteur de textures pour en avoir plusieurs
		std::vector<sf::Sprite> spriteV_; ///< Vecteur de sprites pour en avoir plusieurs

		//Son
		sf::SoundBuffer soundbuffer_;
		sf::Sound sound_;
		std::vector<std::unique_ptr<sf::SoundBuffer>> soundbufferV_;
		std::vector<sf::Sound> soundV_;

};

#endif // CAPACITE_H
