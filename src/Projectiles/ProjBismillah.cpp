#include "ProjBismillah.h"
#include <cmath>


ProjBismillah::ProjBismillah(Ecran& ecran, std::shared_ptr<Entite> lanceur, std::vector<sf::Sprite>& sprite, std::vector<sf::Sound>& sound, Equipe equipe) :
	Projectile(ecran), largeur_max_{ (float)sprite.at(0).getTexture()->getSize().x}
{
	// Weak pointeur vers lanceur
	lanceur_ = lanceur;

	// Gestion du sprite
	sprites_ = sprite;

	// Origines
	sprites_.at(0).setOrigin(sprites_.at(0).getGlobalBounds().width / 2.0f, sprites_.at(0).getGlobalBounds().height / 2.0f); //boule de charge

	// Gestion du son
	sounds_ = sound;
	if (!sounds_.empty()) sounds_.front().play(); //son joué à la création du projectile	

	// Cercle englobant
	//TODO fonction Englobeuse
	const float y = lanceur->getPosition().y;
	const double R = hypot(y / 2.0, largeur_max_ / 2.0);
	cercleEnglobant_ = sf::CircleShape(R);	//l'origine est dynamique car le cercle change de taille

	// Hitbox 
	forme_.emplace_back(new sf::RectangleShape());	//l'origine est dynamique car le rectangle change de taille

    // Caractéristiques de code
    equipe_ = equipe;
    actif_ = false;
    collisionnable_ = false;
    invincibilable_ = false;

	// Stats
    degatsCollision_ = 5;

}

void ProjBismillah::gestion()
{
    assert(dynamic_cast<sf::RectangleShape*>(forme_.front().get()) != nullptr);
	assert(sprites_.at(0).getTexture() != nullptr);

	//TODO PG comment chopper un shared proprement à partir de l'attribut ?
	if (auto lanceur = lanceur_.lock()) {

		const float largeur_vaisseau = lanceur->getTailleSprite().x;
		const float hauteur_vaisseau = lanceur->getTailleSprite().y;

		const float cast_frames = 1209; //temps total pour les deux phases croissance/décroissance //1129ms : temps du son Bismilllah
		const float charge_frames = 1129; //temps de charge
		const float stationnaire_frames = 4032; //temps à l'état stationnaire entre les phases croissance et décroissance

		if (t_age_.asMilliseconds() <= charge_frames)//changement de la taille de la boule de chargement
		{
			sprites_.at(0).setScale(sqrt(t_age_.asMilliseconds() / charge_frames), sqrt(t_age_.asMilliseconds() / charge_frames));
		}
		//rayon croissant
		else if (t_age_.asMilliseconds() <= cast_frames / 2.0f + charge_frames)
		{
			actif_ = true;
			//interpolation linéaire pour que la largeur max soit atteinte en cast_frames images après le temps de charge_boule
			float largeur_actuelle = 2 * largeur_max_ * ((t_age_.asMilliseconds() - charge_frames) / (cast_frames));
			//hitbox
			dynamic_cast<sf::RectangleShape*>(forme_.at(0).get())->setSize({ largeur_actuelle, lanceur->getPosition().y });
			//sprite
			sf::RectangleShape sprite({ largeur_actuelle, lanceur->getPosition().y });
			sprite.setOrigin(largeur_actuelle / 2.0f, lanceur->getPosition().y);
			sprite.setPosition({ lanceur->getPosition().x, lanceur->getPosition().y - hauteur_vaisseau });
			sprite.setTexture(sprites_.at(1).getTexture());
			ecran_.getWindow().draw(sprite);
		}
		//rayon stationnaire
		else if (t_age_.asMilliseconds() <= cast_frames / 2.0f + charge_frames + stationnaire_frames)
		{
			//hitbox
			dynamic_cast<sf::RectangleShape*>(forme_.at(0).get())->setSize({ largeur_max_, lanceur->getPosition().y });
			//sprite
			sf::RectangleShape sprite({ largeur_max_, lanceur->getPosition().y });
			sprite.setOrigin(largeur_max_ / 2.0f, lanceur->getPosition().y);
			sprite.setPosition({ lanceur->getPosition().x, lanceur->getPosition().y - hauteur_vaisseau });
			sprite.setTexture(sprites_.at(1).getTexture());
			ecran_.getWindow().draw(sprite);
		}
		//rayon décroissant
		else if (t_age_.asMilliseconds() <= cast_frames + charge_frames + stationnaire_frames)
		{
			//interpolation linéaire inverse pour que la largeur max soit atteinte en cast_frames images après le temps de charge_boule
			float largeur_actuelle = 2 * largeur_max_ * (1 - ((t_age_.asMilliseconds() - charge_frames - stationnaire_frames) / cast_frames));
			//décroissance de la boule de charge avec le rayon
			sprites_.at(0).setScale(largeur_actuelle / sprites_.at(0).getGlobalBounds().width, largeur_actuelle / sprites_.at(0).getGlobalBounds().height);
			//hitbox
			dynamic_cast<sf::RectangleShape*>(forme_.at(0).get())->setSize({ largeur_actuelle, lanceur->getPosition().y });
			//sprite
			sf::RectangleShape sprite({ largeur_actuelle, lanceur->getPosition().y });
			sprite.setOrigin(largeur_actuelle / 2.0f, lanceur->getPosition().y);
			sprite.setPosition({ lanceur->getPosition().x, lanceur->getPosition().y - hauteur_vaisseau });
			sprite.setTexture(sprites_.at(1).getTexture());
			ecran_.getWindow().draw(sprite);
		}

		//affichage boule de chargement à la position du vaisseau
		sprites_.at(0).setPosition({ lanceur->getPosition().x,lanceur->getPosition().y - hauteur_vaisseau });
		ecran_.getWindow().draw(sprites_.at(0));

		//si les animations sont finies, on tue le projectile
		if (t_age_.asMilliseconds() > cast_frames + charge_frames + stationnaire_frames)
		{
			detruit_ = true;
			actif_ = false;
		}

		// Si le projectile est actif (si l'âge a dépassé charge_frames)
		if (actif_)
		{
			// Repositionnement du cercle englobant
			double R = hypot(lanceur->getPosition().y / 2.0, largeur_max_ / 2.0);
			cercleEnglobant_.setRadius(R);
			cercleEnglobant_.setOrigin(R, R);
			cercleEnglobant_.setPosition(lanceur->getPosition().x, lanceur->getPosition().y / 2.0f);

			// Modification de la position de la hitbox (rectangle)
			//forme_.at(0)->setPosition({ lanceur->getPosition().x - forme_.at(0)->getGlobalBounds().width / 2.0f , - hauteur_vaisseau / 2.0f });
			setPosition({ lanceur->getPosition().x - forme_.at(0)->getGlobalBounds().width / 2.0f , -hauteur_vaisseau / 2.0f });

			//Mode debug
			//bool force_debug = true;
			afficher_debug();
		}

		t_age_ += ecran_.getTempsFrame();
	}
}

void ProjBismillah::agit(Entite & e)
{
    e.recoitDegats(degatsCollision_);
}
