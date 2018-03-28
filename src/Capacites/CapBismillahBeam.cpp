#include "CapBismillahBeam.h"
#include "../Projectiles/ProjBismillah.h"

CapBismillah::CapBismillah(Ecran& ecran, const std::weak_ptr<Entite>& lanceur) :
	Capacite(ecran, lanceur)
{
	//Caractéristiques
	t_lastuse_.restart();
	cooldown_ = sf::milliseconds(20000);
	nom_ = "Bismillah";

	//Icône
	icone_.setTexture(*ecran.getChargeur().getTexture("icone.bism"));
	affiche_ = true;
	
	//Sprites
	for (size_t i = 1; i < 4; ++i) textureV_.at(i)->setRepeated(true); //mode repeated
	for(size_t i = 0; i < 4; ++i) spriteV_.emplace_back(sf::Sprite(*textureV_.at(i)));

    //Sons
    soundbuffer_.loadFromFile("../../rc/Sounds/Capacites/Bismillah.wav");
    sound_.setBuffer(soundbuffer_);
    sound_.setLoop(false);
}

void CapBismillah::utiliser(proj_container& projectiles)
{
	// Si la compétence est disponible
	if (t_ >= cooldown_)
	{
		// Début du timer
		t_ = 0;
		frames_ = 0;
	}

}

void CapBismillah::actualiser(proj_container& projectiles)
{
	// Création du projectile au moment où la compétence est lancée
	if (frames_ == 0)
	{
		proj_ptr temp(new ProjBismillah(vaisseau, spriteV_, textureV_, sound_, JOUEUR));
		projectiles.push_back(temp);

		sound_.play();//son au lancement
	}

	// Si la compétence est en cooldown, on actualise le timer
	if (t_ < cooldown_)
	{
		t_ += tempsEcoule;
		frames_++;
	}
}