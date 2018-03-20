#include "ProjBismillah.h"



ProjBismillah::ProjBismillah(Entite* lanceur, std::vector<sf::Sprite> spriteV_, sf::Sound sound, Equipe equipe)
{
	////Gestion du son
	sound_.play(); //son au lancement

	// Hitbox
	float x = lanceur->getPosition().x;
	double R = hypot(abs(static_cast<float>(ECRAN_L) - x) / 2, 96 / 2);
	cercleEnglobant_ = sf::CircleShape(R);
	cercleEnglobant_.setOrigin(R, R);
	cercleEnglobant_.setPosition(96/2, abs(static_cast<float>(ECRAN_L) - x) / 2);
	forme_.emplace_back(new sf::RectangleShape({ 96, abs(static_cast<float>(ECRAN_L) - x) }));

	// Attributs d'Entite
	equipe_ = equipe;
	actif_ = true;
	collisionable_ = false;

	degatsColl_ = 100;

	//Attributs propres
	lanceur_ = lanceur;


}

void ProjBismillah::gestion(sf::RenderWindow & window, sf::Time tempsEcoule)
{
	if (age_ < 10)
	{
		spriteV_.at(0).setPosition({ lanceur_->getPosition() });
		window.draw(spriteV_.at(0));
	}
}

void ProjBismillah::agit(Entite & e)
{
}
