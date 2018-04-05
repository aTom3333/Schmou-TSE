#include "ProjBoing.h"
#include "../constantes.h"
#include <cmath>

ProjBoing::ProjBoing(Ecran& ecran, std::shared_ptr<Entite> lanceur, std::vector<sf::Sprite>& sprite, std::vector<sf::Sound>& sound, Equipe equipe) :
	Projectile(ecran)
{
	// Weak pointeur vers lanceur
	lanceur_ = lanceur;

	// Gestion du sprite
	sprites_ = sprite;

	// Origines
	origine_ = { 16,16 }; //basé sur image ballePaques(32x32)
	sprites_.at(0).setOrigin({ 16,16 });

	// Gestion du son
	sounds_ = sound;

	// Cercle englobant
	//TODO utiliser la fonction Englobeuse
	cercleEnglobant_ = sf::CircleShape(hypot(16, 16));
	cercleEnglobant_.setOrigin(16, 16);

	// Hitbox
	forme_.emplace_back(new sf::RectangleShape({ 16,16 }));
	forme_.at(0)->setOrigin({ 16,16 });

	// Caractéristiques de code
	equipe_ = equipe;
	innate_ = true;

	// Stats
	pv_ = pvM_ = 10;
	degatsCollision_ = 30; //TODO PG xlanceur.stats().atk

	vit_ = vitM_ = 700;
	rotation_ = rand() % 100 / (float)100. * 2 * PI; // TODO CL rand c++

	rayonCirc_ = hypot(lanceur->getTaille().x, lanceur->getTaille().y);

	// Position de départ
	setPosition({ lanceur->getPosition().x + rayonCirc_*cos(rotation_),  lanceur->getPosition().y - rayonCirc_*sin(rotation_) });
}


void ProjBoing::gestion()
{
	auto& window = ecran_.getWindow();
	auto tempsEcoule = ecran_.getTempsFrame();

	move();

	rotationSpr_ += 500 * tempsEcoule.asSeconds();
	sprites_.at(0).setRotation(rotationSpr_);

	//TODO CL écrire "sounds_.front().play()" au rebond

	if (getPosition().x < 0)
	{
		setPosition({ 0, getPosition().y });
		setRotation(-rotation_);
	}
		

	afficher();
}

void ProjBoing::agit(Entite& proj)
{
	proj.recoitDegats(degatsCollision_);
	detruit_ = true;
}

