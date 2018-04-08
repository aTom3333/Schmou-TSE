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
		* @param projectile Vecteur de shared_ptr sur tous les projectiles présent à l'écran
		*
		* Fonction virtuelle qui gère la création de projectiles et des modifications à apporter au vaisseau
		*/
		virtual void actualiser(proj_container &projectiles) = 0;
		

		//fonctions relatives à l'icone
		//TODO PG à documenter
		void afficherNom() { ecran_.getWindow().draw(text_); };
		void gestionIcon();
		void initIcon(size_t i);
		
		// Getters
		sf::Time getCooldown() const { return cooldown_; };
		sf::Time getTime() const { return t_lastuse_; };
		const std::string& getNom() const { return nom_; };
		const sf::Sprite& getIcon() const { return icone_; };
		const sf::RectangleShape& getMasque() const { return masque_; };
		const sf::Text& getText() const { return text_; };
		bool getAffiche() { return afficheIcone_; };
		bool getTir() { return tir_; };
		const std::vector<sf::Sound>& getSounds_() const { return sounds_; }	

		void setAutoAim(bool aimbot) { aimbot_ = aimbot; }
	protected:
		// Référence vers l'écran
		Ecran& ecran_;

		//Caractéristiques de code
		bool tir_ = false; /// < True si tir principal 1 ou 2

		//Caractéristiques de jeu
		std::string nom_; /// Nom de la compétence
		size_t niveau_ = 0; /// Niveau, à partir de 1
		bool aimbot_ = false;///<True si en état visée automatique

		sf::Time cooldown_; /// Temps à attendre avant de pouvoir utiliser la capacité à nouveau
		sf::Time t_longevite_; ///Temps après lequel le projectile issu disparait
		sf::Time t_lastuse_; /// Temps écoulé depuis la dernière activation de la compétence

		//Texture
		std::vector<sf::Sprite> sprites_; ///< Vecteur de sprites pour en avoir plusieurs

		//Son
		std::vector<sf::Sound> sounds_;

		//Icône
		sf::Font font_;
		sf::Text text_; /// < Nom affiché en jeu
		bool afficheIcone_ = false; /// < true si le sprite de l'icone est affiché
		sf::Sprite icone_;
		sf::RectangleShape masque_;
    
        // Lanceur
        std::weak_ptr<Entite> lanceur_;

};

#endif // CAPACITE_H
