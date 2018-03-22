#include "ProjBismillah.h"
#include <cmath>


ProjBismillah::ProjBismillah(const Entite& lanceur, std::vector<sf::Sprite>& spriteV, sf::Sound sound, Equipe equipe) :
	lanceur_(lanceur)
{
	//Gestion du son
	sound.play();//TODO PG pourquoi tu ne joues pas ??

	//Sprites
	spriteV_ = spriteV;

	// Hitbox 
	//TODO PG � revoir m�me si �a sert � rien avec CL
	float y = lanceur.getPosition().y;
	double R = hypot(y / 2.0, 96.0 / 2.0);
	cercleEnglobant_ = sf::CircleShape(R);
	cercleEnglobant_.setOrigin(R, R);
	cercleEnglobant_.setPosition(96.0 / 2.0, y / 2.0);
	forme_.emplace_back(new sf::RectangleShape({ 96, y }));//o� est la pos de la forme_ ?

	// Attributs d'Entite
	equipe_ = equipe;
	actif_ = true;
	collisionnable_ = false;

	degatsColl_ = 100;

}

void ProjBismillah::gestion(sf::RenderWindow & window, sf::Time tempsEcoule)
{
	int cast_frames = 50; //nombre de frames pour caster le rayon apr�s le chargement
	int offset = 70; //nombres de frames de charge

	if (age_ < offset)
	{
		spriteV_.at(0).setPosition({ lanceur_.getPosition().x-218, lanceur_.getPosition().y - 282 });
		window.draw(spriteV_.at(0));
	}
	else if (age_ < offset + 1 * cast_frames / 6.0 || (offset + 5 * cast_frames / 6.0 < age_ && age_ < offset + 6 * cast_frames / 6.0))
	{
		for (float i = trunc(lanceur_.getPosition().y) ; i > -1; i-=0.99)
		{
			spriteV_.at(1).setPosition({ (float)lanceur_.getPosition().x - 16, (float)i });
			window.draw(spriteV_.at(1));
		}
	}
	else if (age_ < offset + 2 * cast_frames / 6.0 || (offset + 4 * cast_frames / 6.0 < age_ && age_ < offset + 5 * cast_frames / 6.0))
	{
		for (float i = trunc(lanceur_.getPosition().y); i > -1; i -= 0.99)
		{
			spriteV_.at(2).setPosition({ (float)lanceur_.getPosition().x - 16, (float)i });
			window.draw(spriteV_.at(2));
		}

	}
	else if (age_ < offset + 4 * cast_frames / 6.0)
	{
		for (float i = trunc(lanceur_.getPosition().y); i > -1; i -= 0.99)
		{
			spriteV_.at(3).setPosition({ (float)lanceur_.getPosition().x - 16, (float)i });
			window.draw(spriteV_.at(3));
		}

	}

	++age_;
}

void ProjBismillah::agit(Entite & e)
{
	e.getDegatsColl_();
}
