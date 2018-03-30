#include "ProjBouclierRond.h"
#include <cmath>

ProjBouclierRond::ProjBouclierRond(Ecran& ecran, std::shared_ptr<Entite> lanceur, std::vector<sf::Sprite>& sprite, std::vector<sf::Sound>& sound, Equipe equipe):
	Projectile(ecran)
{
	// Weak pointeur vers lanceur
	lanceur_ = lanceur;

	// Gestion du sprite
	sprites_ = sprite;

	//Origines
	origine_ = { sprites_.at(0).getGlobalBounds().width / 2.0f, sprites_.at(0).getGlobalBounds().height / 2.0f };
	sprites_.at(0).setOrigin({ sprites_.at(0).getGlobalBounds().width / 2.0f, sprites_.at(0).getGlobalBounds().height / 2.0f });

	//Gestion du son
	sounds_ = sound;
	if (!sounds_.empty())sounds_.front().play();//son joué à la création du projectile

	// cercle englobant
	//TODO utiliser la fonction Englobeuse
	const float R = sprites_.at(0).getGlobalBounds().width / 2.0f;
	cercleEnglobant_ = sf::CircleShape(R);
	cercleEnglobant_.setOrigin(R, R);

	//Hitbox : il s'agit ici du cercle englobant
	forme_.emplace_back(new sf::CircleShape(cercleEnglobant_));

	// Caractéristiques de code
	equipe_ = equipe;
	actif_ = true;
	invincibilable_ = false;

	//Stats
	pv_ = pvM_ = 5000;

	degatsCollision_ = 0; //le bouclier n'inflige ici aucun dégat (passif)

	t_longevite_ = sf::milliseconds(7000);

	//position de départ
	setPosition({ lanceur->getPosition().x ,  lanceur->getPosition().y });

	//Comportement spécifique
	lanceur->setBouclier(pv_);
	lanceur->setBouclierM(pvM_);
	lanceur->setCollisionnable(false);//TODO PG bloquer au bouclier en cas de collision
}

void ProjBouclierRond::gestion()
{
	auto& window = ecran_.getWindow();
	
	if (auto lanceur = lanceur_.lock())
	{
		setPosition({ lanceur->getPosition().x, lanceur->getPosition().y });

		lanceur->setBouclier(pv_);

		afficher();

		if (t_age_ >= t_longevite_)
		{
			detruit_ = true;
			lanceur->setBouclier(0);
			lanceur->setBouclierM(0);
			lanceur->setCollisionnable(true);
		}
		else t_age_ += ecran_.getTempsFrame();
	}
}


void ProjBouclierRond::agit(Entite& proj)
{
	proj.recoitDegats(degatsCollision_);//inflige dégats
	//change d'opacité selon sa vie
	sf::Uint8 alpha = (sf::Uint8)(pv_ / pvM_ * 255);
	alpha < 50 ? 50 : alpha;//seuil minimum sinon le bouclier est très peu visible à faible vie
	sprites_.front().setColor({ 255, 255, 255, alpha });
	if (pv_ <= 0)
		detruit_ = true;
}