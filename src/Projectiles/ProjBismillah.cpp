#include "ProjBismillah.h"
#include <cmath>


ProjBismillah::ProjBismillah(const Entite& lanceur, std::vector<sf::Sprite>& spriteV, std::vector<std::shared_ptr<sf::Texture>>& textureV, sf::Sound sound, Equipe equipe) : 
	largeur_max_{ (float)textureV.at(0)->getSize().x }, lanceur_(lanceur)
{
    //Gestion du son
    sound.play();//TODO PG pourquoi tu ne joues pas ??

    //Sprites
    sprites_ = spriteV;
	textureV_ = textureV;

	// Hitbox 
	const float y = lanceur.getPosition().y;
	const double R = hypot(y / 2.0, largeur_max_ / 2.0);
	cercleEnglobant_ = sf::CircleShape(R);
	forme_.emplace_back(new sf::RectangleShape());

	//Origine
	sprites_.at(0).setOrigin(sprites_.at(0).getGlobalBounds().width / 2.0f, sprites_.at(0).getGlobalBounds().height / 2.0f);//boule de charge

    // Attributs d'Entite
    equipe_ = equipe;
    actif_ = false;
    collisionnable_ = false;
    invincibilite_ = false;

    degatsColl_ = 500;

}

void ProjBismillah::gestion(sf::RenderWindow & window, sf::Time tempsEcoule)
{
    assert(dynamic_cast<sf::RectangleShape*>(forme_.front().get()) != nullptr);
	assert(textureV_.at(1));

	const float largeur_vaisseau = lanceur_.getTaille().x;
	const float hauteur_vaisseau = lanceur_.getTaille().y;

    const float cast_frames = 75; //nombre de frames total pour les deux phases croissance/décroissance
    const float charge_frames = 70; //nombres de frames de charge
	const float stationnaire_frames = 250; //nombre de frames à l'état stationnaire entre les phases croissance et décroissance

    if (age_ <= charge_frames)//changement de la taille de la boule de chargement
    {
        sprites_.at(0).setScale(sqrt(age_ / charge_frames), sqrt(age_ / charge_frames));
    }
	//rayon croissant
	else if (age_ <= cast_frames / 2.0f + charge_frames)
    {
        actif_ = true;
		//interpolation linéaire pour que la largeur max soit atteinte en cast_frames images après le temps de charge_boule
		float largeur_actuelle = 2*largeur_max_ * ((age_ - charge_frames) / (cast_frames));
		//hitbox
        dynamic_cast<sf::RectangleShape*>(forme_.at(0).get())->setSize({ largeur_actuelle, lanceur_.getPosition().y });
		//sprite
		sf::RectangleShape sprite({ largeur_actuelle, lanceur_.getPosition().y });
		sprite.setOrigin(largeur_actuelle / 2.0f, lanceur_.getPosition().y);
		sprite.setPosition({ lanceur_.getPosition().x, lanceur_.getPosition().y - hauteur_vaisseau });
		sprite.setTexture(textureV_.at(3).get());
		window.draw(sprite);
    }
	//rayon stationnaire
	else if (age_ <= cast_frames / 2.0f + charge_frames + stationnaire_frames)
	{
		//hitbox
		dynamic_cast<sf::RectangleShape*>(forme_.at(0).get())->setSize({ largeur_max_, lanceur_.getPosition().y });
		//sprite
		sf::RectangleShape sprite({ largeur_max_, lanceur_.getPosition().y });
		sprite.setOrigin(largeur_max_ / 2.0f, lanceur_.getPosition().y);
		sprite.setPosition({ lanceur_.getPosition().x, lanceur_.getPosition().y - hauteur_vaisseau });
		sprite.setTexture(textureV_.at(3).get());
		window.draw(sprite);
	}
	//rayon décroissant
	else if (age_ <= cast_frames + charge_frames + stationnaire_frames)
	{
		//interpolation linéaire inverse pour que la largeur max soit atteinte en cast_frames images après le temps de charge_boule
		float largeur_actuelle = 2*largeur_max_ * (1 - ((age_ - charge_frames - stationnaire_frames) / cast_frames));
		//décroissance de la boule de charge avec le rayon
		sprites_.at(0).setScale(largeur_actuelle / sprites_.at(0).getGlobalBounds().width, largeur_actuelle / sprites_.at(0).getGlobalBounds().height);
		//hitbox
		dynamic_cast<sf::RectangleShape*>(forme_.at(0).get())->setSize({ largeur_actuelle, lanceur_.getPosition().y });
		//sprite
		sf::RectangleShape sprite({ largeur_actuelle, lanceur_.getPosition().y });
		sprite.setOrigin(largeur_actuelle / 2.0f, lanceur_.getPosition().y);
		sprite.setPosition({ lanceur_.getPosition().x, lanceur_.getPosition().y - hauteur_vaisseau});
		sprite.setTexture(textureV_.at(3).get());
		window.draw(sprite);
	}
	 
	//affichage boule de chargement à la position du vaisseau
	sprites_.at(0).setPosition({ lanceur_.getPosition().x,lanceur_.getPosition().y - hauteur_vaisseau });
	window.draw(sprites_.at(0));

	//si les animations sont finies, on tue le projectile
    if (age_ > cast_frames + charge_frames + stationnaire_frames)
    {
        detruit_ = true;
        actif_ = false;
    }

	// Si le projectile est actif (si l'âge a dépassé charge_frames)
	if (actif_)
	{
		// Repositionnement du cercle englobant
		double R = hypot(lanceur_.getPosition().y / 2.0, largeur_max_ / 2.0);
		cercleEnglobant_.setRadius(R);
		cercleEnglobant_.setOrigin(R, R);
		cercleEnglobant_.setPosition(lanceur_.getPosition().x , lanceur_.getPosition().y / 2.0f);

        // Modification de la position de la hitbox (rectangle)
		//forme_.at(0)->setPosition({ lanceur_.getPosition().x - forme_.at(0)->getGlobalBounds().width / 2.0f , - hauteur_vaisseau / 2.0f });
		setPosition({ lanceur_.getPosition().x - forme_.at(0)->getGlobalBounds().width / 2.0f , - hauteur_vaisseau / 2.0f });

		// HACK CL Affichage de hitbox
		debug_ = false;
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
