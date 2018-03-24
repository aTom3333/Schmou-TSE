#ifndef PROJ_BISMILLAH_H
#define PROJ_BISMILLAH_H

#include "Projectile.h"

class ProjBismillah : public Projectile
{
public:
	/**
	* @fn ProjBismillah
	* @brief Constructeur
	* @param x Abscisse de la position de départ du projectile
	* @param y Ordonnée de la position de départ du projectile
	* @param sound Son par défaut donné par la capacité qui crée le proj
	* @param equipe Représente l'équipe depuis _constante.h : enum Equipe
	*
	* Créer un projectile piou à la position donnée en paramètre
	*/
	ProjBismillah(const Entite& lanceur, std::vector<sf::Sprite>& spriteV, std::vector<std::shared_ptr<sf::Texture>>& textureV, sf::Sound sound, Equipe equipe = NEUTRE);

	void gestion(sf::RenderWindow& window, sf::Time tempsEcoule) override;

	void agit(Entite& e) override;

private:
	const Entite& lanceur_;
	size_t age_ = 0;
	const float largeur_max_;

};



#endif // !PROJ_BISMILLAH_H

