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
	cercleEnglobant_.setPosition(16, 16);

	// Hitbox
	forme_.emplace_back(new sf::RectangleShape({ 16,16 }));
	forme_.at(0)->setOrigin({ 16,16 });

	// Caractéristiques de code
	equipe_ = equipe;

	// Stats
	degatsColl_ = 30; //TODO PG xlanceur.stats().atk

	vit_ = vitM_ = 0.400;
	rotation_ = rand() % 100 / 100 * 2 * PI; // TODO CL rand c++

	rayonCirc_ = hypot(lanceur->getTaille().x, lanceur->getTaille().y);

	// Position de départ
	setPosition({ lanceur->getPosition().x + rayonCirc_*cos(rotation_),  lanceur->getPosition().y + rayonCirc_*cos(rotation_) });
}


void ProjBoing::gestion()
{
	auto& window = ecran_.getWindow();
	auto tempsEcoule = ecran_.getTempsFrame();
	move();

	rotation_ += 100 * tempsEcoule.asSeconds();
	sprites_.at(0).setRotation(rotation_);

	//TODO écrire "sounds_.front().play()" au rebond

	afficher();
}

void ProjBoing::agit(Entite& proj)
{
	proj.recoitDegats(degatsColl_);
	detruit_ = true;
}

