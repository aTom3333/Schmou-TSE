#include "CapBismillahBeam.h"
#include "../Projectiles/ProjBismillah.h"

CapBismillah::CapBismillah()
{
	//Caractéristiques
	t_ = frames_ = cooldown_ = 1000;
	//TODO ici le warning pourrait être important (frames_ : float vers uint)
	nom_ = "Bismillah";

	//Icône
	capText_.loadFromFile("../../rc/Icones_Caps/laser.png");
	capacite_.setTexture(capText_);

	//Son
	soundbuffer_.loadFromFile("../../rc/Sounds/Capacites/Bismillah.wav");
	sound_.setBuffer(soundbuffer_);
	sound_.setLoop(false);
}

void CapBismillah::utiliser(int x, int y)
{
	// Si la compétence est disponible
	if (t_ >= cooldown_)
	{
		//Son au lancement
		sound_.play();
		// Début du timer
		t_ = 0;
		frames_ = 0;
		// Initialisation de l'endroit ou la compétence a été utilisée
		debutX_ = x;
		debutY_ = y;
	}

}

void CapBismillah::actualiser(std::vector<Projectile*>& projectiles, Entite& vaisseau, float tempsEcoule)
{
	// Création du projectile au moment où la compétence est lancée
	if (frames_ == 0)
	{
		//TODO bug
		ProjBismillah *temp = new ProjBismillah(debutX_, debutY_, sound_, ALLIE);
		projectiles.push_back(temp);
	}

	// Si la compétence est en cooldown, on actualise le timer
	if (t_ < cooldown_)
	{
		t_ += tempsEcoule;
		frames_++;

	}

}