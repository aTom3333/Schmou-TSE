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
		explicit Capacite(Ecran& ecran, std::weak_ptr<Entite> lanceur) : 
            ecran_{ecran}, lanceur_{std::move(lanceur)} {};
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
		*
		* Fonction virtuel qui initialise la position de départ et le timer
		*/
		virtual void utiliser(proj_container& projectile) = 0;
		/**
		* @fn actualiser
		* @brief Fonction virtuel qui active les effets de la capacité
		* @param projectile Vecteur de tout les projectiles présent à l'écran
		* @param vaisseau Vaisseau qui a activé la compétence
		* @param tempEcoule Temps écoulé depuis la dernière boucle
		*
		* Fonction virtuel qui gère la création de projectiles et des modifications à apporter au vaisseau
		*/
		virtual void actualiser(proj_container &projectiles) = 0;

		void initIcon(int i);
		
		// Getters
		sf::Time getCooldown() const { return cooldown_; };
		sf::Time getTime() const { return t_lastuse_.getElapsedTime(); };
		const std::string& getNom() const { return nom_; };
		const sf::Sprite& getIcon() const { return capacite_; };
		const sf::RectangleShape& getMasque() const { return masque_; };
		const sf::Text& getText() const { return text_; };
		bool getAffiche() { return affiche_; };
		bool getTir() { return tir_; };
		const std::vector<sf::Sound>& getSounds_() const { return sounds_; }



		void afficherNom(sf::RenderWindow &window) { window.draw(text_); };
		void gestionIcon();
		

	protected:
		// Référence vers l'écran
		Ecran& ecran_;
	
		std::shared_ptr<sf::Texture> capTexture_;
		sf::Sprite capacite_;
		sf::RectangleShape masque_;
		sf::Font font_;
		sf::Text text_;
		bool affiche_ = false;
		bool tir_ = false;
		std::string nom_; /// Nom de la compétence
		unsigned int niveau_; /// Niveau, à partir de 1

		sf::Time cooldown_; /// Temps à attendre avant de pouvoir utiliser la capacité à nouveau
		sf::Time longevite_; ///Temps après lequel le projectile issu disparait

		sf::Clock t_lastuse_; /// Temps écoulé depuis la dernière activation de la compétence

		bool autoAim; ///état visée auto

		//Texture
		std::vector<sf::Sprite> sprites_; ///< Vecteur de sprites pour en avoir plusieurs

		//Son
		std::vector<sf::Sound> sounds_;
    
        // Lanceur
        std::weak_ptr<Entite> lanceur_;

};

#endif // CAPACITE_H
