#include "CapDash.h"
#include "../Interface/Input.h"

CapDash::CapDash()
{
	capText_.loadFromFile("../../rc/Pictos_Caps/tir.png");
	capacite_.setTexture(capText_);
	cooldown_ = 500;
	frames_ = cooldown_; //TODO ici le warning pourrait être important (float vers uint)
	t_ = cooldown_;
	nom_ = "Dash";
	tir_ = true;

	//son
	soundbuffer_.loadFromFile("../../rc/Sounds/Capacites/dash.wav");
	sound_.setBuffer(soundbuffer_);
	sound_.setLoop(false);

}


void CapDash::utiliser(int x, int y)
{
	// Si la compétence est disponible
	if (t_ >= cooldown_) {
		// Début du timer
		t_ = 0;
		frames_ = 0;
		sound_.play();
	}
}


void CapDash::actualiser(std::vector<Projectile*>& projectiles, Entite& vaisseau, float tempsEcoule)
{
	//TODO bon il est 3 heures faut que j'aille dormir jpp Thomas faut que tu m'aides :'(

	// Augmente la vitesse  à l'activation
	if(frames_ == 0)
		vaisseau.changeSpeed(2500);
	// Retourne à la vitesse de base au bout de 6 frames
	if(frames_ == 6)
		vaisseau.changeSpeed(-2500);

	// Si la compétence est en cooldown, on actualise le timer
	if (t_ < cooldown_)
	{
		t_ += tempsEcoule;
		frames_++;

	}
		

}
