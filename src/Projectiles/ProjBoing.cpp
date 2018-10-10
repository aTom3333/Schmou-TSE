#include "ProjBoing.h"
#include "../constantes.h"
#include "../Utilitaires/Divers.h"
#include "../Utilitaires/utilities.h"

#include <cmath>
#include <iostream>


template <typename T> int signe(T val) {
	return (T(0) < val) - (val < T(0));
}

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
	const float R = hypot(16, 16);
	cercleEnglobant_ = sf::CircleShape(R);
	cercleEnglobant_.setOrigin(R,R);

	// Hitbox
	forme_.emplace_back(new sf::CircleShape(R/2));
	forme_.at(0)->setOrigin({ R / 2, R / 2 });

	// Caractéristiques de code
	equipe_ = NEUTRE;
	//innate_ = true;

	// Stats
	pv_ = pvM_ = 100;
	degatsCollision_ = 100; //TODO PG * (fois) lanceur.stats().atk
	vit_ = vitM_ = 700;
	rotation_ = random() % 360;
	//rotation_ = 45 * (rand()%8);

	// Position de départ
	float X = lanceur->getPosition().x + lanceur->getTailleSprite().x * -cos(rotation_*PI / 180) ,
		  Y = lanceur->getPosition().y + lanceur->getTailleSprite().y * -sin(rotation_*PI / 180);
	if (X < 0)X = 0;
	else if (X > ECRAN_L)X = ECRAN_L;
	if (Y < 0)Y = 0;
	else if (Y > ECRAN_H)Y = ECRAN_H;
	setPosition({ X, Y });
}


void ProjBoing::gestion()
{
	auto& window = ecran_.getWindow();
	auto tempsEcoule = ecran_.getTempsFrame();

	const float X = getPosition().x;
	const float Y = getPosition().y;

	const short sens_vertical = (180 < rotation_ && rotation_ < 360) ? -1 : ((rotation_ == 180 || rotation_ == 360) ? 0 : 1);
	const short sens_horizontal = (90 < rotation_ && rotation_ < 270) ? -1 : ((rotation_ == 90 || rotation_ == 270) ? 0 : 1);

	const float R = cercleEnglobant_.getRadius() / 2;

	if (X - R < 0)
	{
		if (sens_vertical == 1)
			rotation_ = 180 - fmod(rotation_, 90);
		else if (sens_vertical == -1)
			rotation_ = 270 - fmod(rotation_, 90);
		else
			rotation_ = 180; //TODO PG décalage lorsque rebond à angle droite sur la gauche
		sounds_.at(0).play();
		pv_ -= 10;
	}
	else if (X + R > ECRAN_L)
	{
		if (sens_vertical == 1)
			rotation_ = 90 - fmod(rotation_, 90);
		else if (sens_vertical == -1)
			rotation_ = 360 - fmod(rotation_, 90);
		else
			rotation_ = 0;
		sounds_.at(0).play();
		pv_ -= 10;
	}
	else if (Y - R < 0)
	{
		if (sens_horizontal == 1)
			rotation_ = 360 - fmod(rotation_, 90);
		else if (sens_horizontal == -1)
			rotation_ = 270 - fmod(rotation_, 90);
		else
			rotation_ = 270;
		sounds_.at(0).play();
		pv_ -= 10;
	}
	else if (Y + R > ECRAN_H)
	{
		if (sens_horizontal == 1)
			rotation_ = 90 - fmod(rotation_, 90);
		else if (sens_horizontal == -1)
			rotation_ = 180 - fmod(rotation_, 90);
		else
			rotation_ = 90;
		sounds_.at(0).play();
		pv_ -= 10;
	}
	
	//gère la rotation de sprite & hitbox sans changer la rotation_
    const float temp_rotation = getRotation();
    static const float VIT_ANGULAIRE = 500;
	rotate(VIT_ANGULAIRE * tempsEcoule.asSeconds());
	rotation_ = temp_rotation;
		
	move();
	afficher();
}

void ProjBoing::agit(Entite& proj)
{
	proj.recoitDegats(degatsCollision_);
	detruit_ = true;
}

