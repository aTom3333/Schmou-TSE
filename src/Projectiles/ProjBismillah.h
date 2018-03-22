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
	ProjBismillah(Entite* lanceur, std::vector<sf::Sprite>& spriteV, sf::Sound sound, Equipe equipe = NEUTRE);



	void gestion(sf::RenderWindow& window, sf::Time tempsEcoule);

	void agit(Entite& e);

private:
	Entite * lanceur_ = nullptr;
	size_t age_ = 0;
};



#endif // !PROJ_BISMILLAH_H

