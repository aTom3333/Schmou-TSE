#include "CapBoing.h"
#include "CapDash.h"

CapBoing::CapBoing()
{
	t_ = frames_ = cooldown_ = 1000; //TODO PG ici le warning pourrait être important (float vers uint)
	nom_ = "Attaque Test";

	//état
	affiche_ = true;

	//Icône
	capText_.loadFromFile("../../rc/Icones_Caps/attaque_test.png");
	icone_.setTexture(capText_);

	//Son
	soundbuffer_.loadFromFile("../../rc/Sounds/Capacites/boing.wav");
	sound_.setBuffer(soundbuffer_);
	sound_.setLoop(false);

}


CapBoing::~CapBoing()
{
}

void CapBoing::utiliser(int x, int y)
{
	// Si la compétence est disponible
	if (t_ >= cooldown_)
	{
		// Début du timer
		t_ = 0;
		frames_ = 0;
		// Initialisation de l'endroit ou la compétence a été utilisée
		debutX_ = x;
		debutY_ = y;
	}
}

void CapBoing::actualiser(proj_container& projectiles, Entite& vaisseau, float tempsEcoule)
{
    // Juste pour mute les warnings du compilateur
    (void)vaisseau;
    
	// Pour avoir la création des 4 projectile toute les 5 frames
	if (frames_ < 20 && frames_ % 5 == 0)
	{
		// Création d'un nouveau projectile
		proj_ptr temp(new ProjBoing(debutX_, debutY_, sound_));
		projectiles.push_back(temp);
	}

	// Si la compétence est en cooldown, on actualise le timer
	if (t_ < cooldown_)
	{
		t_ += tempsEcoule;
	}
	frames_++;
}
