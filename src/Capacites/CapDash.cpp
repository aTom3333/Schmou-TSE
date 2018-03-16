#include "CapDash.h"
#include "../Interface/Input.h"

CapDash::CapDash()
{
	capText_.loadFromFile("../../rc/Icones_Caps/tir.png");
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
	// Juste pour mute les warnings du compilateur
	(void)x;
	(void)y;
	
	// Si la compétence est disponible
	if (t_ >= cooldown_) {
		// Début du timer
		t_ = 0;
		frames_ = 0;
		sound_.play();
	}
}


void CapDash::actualiser(proj_container& projectiles, Entite& vaisseau, float tempsEcoule)
{
	// Juste pour mute les warnings du compilateur
	(void)projectiles;
	
	//TODO ne se lance que si le lanceur n'est pas immobile

	// Augmente la vitesse  à l'activation
	if (frames_ == 0)
	{
		vaisseau.changeSpeed(2500);
		vaisseau.setNbPositions(15);
		vaisseau.setSmokeTexture(vaisseau.getTexture(), { 120, 120, 120, 120 });
	}
		
	// Retourne à la vitesse de base au bout de 6 frames
	if (frames_ == 6)
	{
		vaisseau.changeSpeed(-2500);
		vaisseau.setNbPositions(0);
	}
		

	// Si la compétence est en cooldown, on actualise le timer
	if (t_ < cooldown_)
	{
		t_ += tempsEcoule;
	}
	
	frames_++;

}
