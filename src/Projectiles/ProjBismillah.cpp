#include "ProjBismillah.h"
#include <cmath>


ProjBismillah::ProjBismillah(const Entite& lanceur, std::vector<sf::Sprite>& spriteV, std::vector<std::shared_ptr<sf::Texture>>& textureV, sf::Sound sound, Equipe equipe) :
    lanceur_(lanceur)
{
    //Gestion du son
    sound.play();//TODO PG pourquoi tu ne joues pas ??

    //Sprites
    spriteV_ = spriteV;
	textureV_ = textureV;

	// Hitbox 
	float y = lanceur.getPosition().y;
	double R = hypot(y / 2.0, 96.0 / 2.0);
	cercleEnglobant_ = sf::CircleShape(R);
	cercleEnglobant_.setOrigin(R, R);
	cercleEnglobant_.setPosition(96.0 / 2.0, y / 2.0);
	forme_.emplace_back(new sf::RectangleShape({ 96, y }));

    // Attributs d'Entite
    equipe_ = equipe;
    actif_ = false;
    collisionnable_ = false;
    invincibilite_ = false;

    degatsColl_ = 350;

}

void ProjBismillah::gestion(sf::RenderWindow & window, sf::Time tempsEcoule)
{
    assert(dynamic_cast<sf::RectangleShape*>(forme_.front().get()) != nullptr);
	assert(textureV_.at(1));

    int cast_frames = 50; //nombre de frames pour caster le rayon après le chargement
    int boule_charge_frames = 70; //nombres de frames de charge

    if (age_ < boule_charge_frames)//changement de la taille de la boule de chargement
    {
        spriteV_.at(0).setScale(sqrt((float)age_ / (float)boule_charge_frames), sqrt((float)age_ / (float)boule_charge_frames));
    }
    else if (age_ < boule_charge_frames + 1 * cast_frames / 6.0 || (boule_charge_frames + 5 * cast_frames / 6.0 < age_ && age_ < boule_charge_frames + 6 * cast_frames / 6.0))
    {
        actif_ = true;
            dynamic_cast<sf::RectangleShape*>(forme_.at(0).get())->setSize({ 32, lanceur_.getPosition().y });
			spriteV_.at(1).setTextureRect({ (int)lanceur_.getPosition().x + 16, 0, 32, (int)lanceur_.getPosition().y });
			spriteV_.at(1).setTexture(*textureV_.at(1).get());
			spriteV_.at(1).setPosition({ lanceur_.getPosition().x + 16, 0 });
            window.draw(spriteV_.at(1));
    }
    else if (age_ < boule_charge_frames + 2 * cast_frames / 6.0 || (boule_charge_frames + 4 * cast_frames / 6.0 < age_ && age_ < boule_charge_frames + 5 * cast_frames / 6.0))
    {
            dynamic_cast<sf::RectangleShape*>(forme_.at(0).get())->setSize({ 64, lanceur_.getPosition().y });
			spriteV_.at(1).setTextureRect({ (int)lanceur_.getPosition().x, 0, 32, (int)lanceur_.getPosition().y });
			spriteV_.at(1).setTexture(*textureV_.at(1).get());
			spriteV_.at(1).setPosition({ lanceur_.getPosition().x, 0 });
			window.draw(spriteV_.at(2));
    }
    else if (age_ < boule_charge_frames + 4 * cast_frames / 6.0)
	{
            dynamic_cast<sf::RectangleShape*>(forme_.at(0).get())->setSize({ 96, lanceur_.getPosition().y });
			spriteV_.at(1).setTextureRect({ (int)lanceur_.getPosition().x - 16, 0, 32, (int)lanceur_.getPosition().y });
			spriteV_.at(1).setTexture(*textureV_.at(1).get());
			spriteV_.at(1).setPosition({ lanceur_.getPosition().x - 16, 0 });
			window.draw(spriteV_.at(3));
	}

	//affichage boule de chargement à la position du vaisseau
	spriteV_.at(0).setPosition({ lanceur_.getPosition().x + 32 - spriteV_.at(0).getGlobalBounds().width / (float)2.0,
		lanceur_.getPosition().y - spriteV_.at(0).getGlobalBounds().height / (float)2.0 });
	window.draw(spriteV_.at(0));

	//si les animations sont finies, on tue le projectile
    if (age_ > cast_frames + boule_charge_frames)
    {
        detruit_ = true;
        actif_ = false;
    }

	// Si le projectile est actif (si l'âge a dépassé boule_charge_frames)
	if (actif_)
	{
		// Repositionnement du cercle englobant
		double R = hypot(lanceur_.getPosition().y / 2.0, 96.0 / 2.0);
		cercleEnglobant_.setRadius(lanceur_.getPosition().y / 2);
		cercleEnglobant_.setOrigin(R, R);
		cercleEnglobant_.setPosition(lanceur_.getPosition().x + 32, lanceur_.getPosition().y / 2);

        // Modification de la position de la hitbox
        setPosition({ lanceur_.getPosition().x + 32 - forme_.at(0)->getGlobalBounds().width/(float)2.0 , 0 });

		// HACK CL Affichage de hitbox
		bool debug_ = false;
		if (debug_)
		{
			auto f = dynamic_cast<sf::RectangleShape*> (forme_.front().get());
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
