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
	actif_ = false;
	collisionnable_ = false;

	degatsColl_ = 350;

}

void ProjBismillah::gestion(sf::RenderWindow & window, sf::Time tempsEcoule)
{
	int cast_frames = 50; //nombre de frames pour caster le rayon apr�s le chargement
	int offset = 70; //nombres de frames de charge

	if (age_ < offset)
	{
        spriteV_.at(0).setScale(sqrt((float)age_ / (float)offset), sqrt((float)age_ / (float)offset));
	}
	else if (age_ < offset + 1 * cast_frames / 6.0 || (offset + 5 * cast_frames / 6.0 < age_ && age_ < offset + 6 * cast_frames / 6.0))
	{
		actif_ = true;
		for (float i = trunc(lanceur_.getPosition().y) ; i > -1; i-=0.99)
		{
			spriteV_.at(1).setPosition({ lanceur_.getPosition().x - 16, i });
			dynamic_cast<sf::RectangleShape*>(forme_.at(0).get())->setSize({ 32, lanceur_.getPosition().y });
			window.draw(spriteV_.at(1));
		}
	}
	else if (age_ < offset + 2 * cast_frames / 6.0 || (offset + 4 * cast_frames / 6.0 < age_ && age_ < offset + 5 * cast_frames / 6.0))
	{
		for (float i = trunc(lanceur_.getPosition().y); i > -1; i -= 0.99)
		{
			spriteV_.at(2).setPosition({ lanceur_.getPosition().x - 16, i });
			dynamic_cast<sf::RectangleShape*>(forme_.at(0).get())->setSize({ 64, lanceur_.getPosition().y });
			window.draw(spriteV_.at(2));
		}

	}
	else if (age_ < offset + 4 * cast_frames / 6.0)
	{
		for (float i = trunc(lanceur_.getPosition().y); i > -1; i -= 0.99)
		{
			spriteV_.at(3).setPosition({ (float)lanceur_.getPosition().x - 16, (float)i });
			dynamic_cast<sf::RectangleShape*>(forme_.at(0).get())->setSize({ 96, lanceur_.getPosition().y });
			window.draw(spriteV_.at(3));
		}

	}
	//affichage boule de chargement
	spriteV_.at(0).setPosition({ lanceur_.getPosition().x + 32 - spriteV_.at(0).getGlobalBounds().width / (float)2.0,
		lanceur_.getPosition().y - spriteV_.at(0).getGlobalBounds().height / (float)2.0 });
	window.draw(spriteV_.at(0));


	if (age_ > cast_frames + offset)
	{
		detruit_ = true;
		actif_ = false;
	}

	// Si le projectile est actif (si l'age � d�pass� l'offste)
	if (actif_)
	{
		// R�cup�ration de la forme du laser
		//TODO PG je pense que c'est un overkill ce test Thomas, la forme sera TOUJOURS un RectangleShape, c'est dans le **constructeur**
		auto f = dynamic_cast<sf::RectangleShape*> (forme_[0].get());
		//
		//// Si la forme du laser est un rectangle 
		//if (f != nullptr)
		//{
		//	// Changement de la taille de la forme du laser
		//	f->setSize({ 96, lanceur_->getPosition().y });
		//}
		
		// Repositionnement du cercle englobant
		double R = hypot(lanceur_.getPosition().y / 2.0, 96.0 / 2.0);
		cercleEnglobant_.setRadius(lanceur_.getPosition().y / 2);
		cercleEnglobant_.setOrigin(R, R);
		cercleEnglobant_.setPosition(lanceur_.getPosition().x + 32, lanceur_->getPosition().y / 2);

		// Modification de la position de la hitbox
		setPosition({ lanceur_.getPosition().x + 32 - forme_.at(0)->getGlobalBounds().width/(float)2.0 , 0 });

		// HACK CL Affichage de hitbox
		bool debug_ = false;
		if (debug_)
		{
			if(f != nullptr)
				f->setFillColor({ 255,100,100,128 });

			for (auto& elem : forme_)
				window.draw(*elem);

			cercleEnglobant_.setFillColor({ 255,100,100,128 });
			window.draw(cercleEnglobant_);
		}
		
	}
	

	++age_;
}

void ProjBismillah::agit(Entite & e)
{
	e.recoitDegats(degatsColl_);
}
