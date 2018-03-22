#include "CapPiou.h"

CapPiou::CapPiou()
{
	//Caractéristiques
	cooldown_ = 100;
	t_ = cooldown_;
	frames_ = cooldown_; //TODO PG ici le warning pourrait être important (float vers uint)
	nom_ = "Canon Laser";
	tir_ = true;

	//Icônes
	capText_.loadFromFile("../../rc/Icones_Caps/tir.png");
	capacite_.setTexture(capText_);

	//Son
	soundbuffer_.loadFromFile("../../rc/Sounds/Capacites/piou.wav");
	sound_.setBuffer(soundbuffer_);
	sound_.setLoop(false);

}


void CapPiou::utiliser(int x, int y)
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

void CapPiou::actualiser(proj_container& projectiles, Entite& vaisseau, float tempsEcoule)
{
    // Juste pour mute les warnings du compilateur
    (void)projectiles;
	(void)vaisseau;
    
	// Création du projectile au moment où la compétence est lancée
	if (frames_ == 0)
	{
		//TODO bug
		proj_ptr temp(new ProjPiou(debutX_, debutY_, sound_, JOUEUR));
		sound_.play();
		projectiles.push_back(temp);
	}

	// Si la compétence est en cooldown, on actualise le timer
	if (t_ < cooldown_)
	{
		t_ += tempsEcoule;
	}
	frames_++;
}
