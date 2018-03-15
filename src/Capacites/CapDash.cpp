#include "CapDash.h"
#include "../Interface/Input.h"

CapDash::CapDash()
{
	capText_.loadFromFile("../../rc/Capacites/tir.png");
	capacite_.setTexture(capText_);
	cooldown_ = 500;
	frames_ = cooldown_; //TODO ici le warning pourrait être important (float vers uint)
	t_ = cooldown_;
	nom_ = "Dash";
	tir_ = true;
}


void CapDash::utiliser(int x, int y)
{
	// Si la compétence est disponible
	if (t_ >= cooldown_) {
		// Début du timer
		t_ = 0;
		frames_ = 0;
	}
}


void CapDash::actualiser(std::vector<Projectile*>& projectiles, Entite& vaisseau, float tempsEcoule)
{
	//if (Input::isMoving()) 
	//TODO bon il est 3 heures faut que j'aille dormir jpp Thomas faut que tu m'aides :'(
	// Augmente la vitesse de 5000 à l'activation
	if(frames_ == 0)
		vaisseau.changeSpeed(5000);
	// Retourne à la vitesse de base au bout de 5 frames
	if(frames_ == 5)
		vaisseau.changeSpeed(-5000);

	// Si la compétence est en cooldown, on actualise le timer
	if (t_ < cooldown_)
	{
		t_ += tempsEcoule;
		frames_++;

	}
		

}
