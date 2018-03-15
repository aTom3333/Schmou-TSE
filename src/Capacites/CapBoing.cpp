#include "CapBoing.h"
#include "CapDash.h"

CapBoing::CapBoing()
{
	cooldown_ = 1000;
	frames_ = cooldown_; //TODO ici le warning pourrait être important (float vers uint)
	t_ = cooldown_;
	nom_ = "Attaque Test";

	capText_.loadFromFile("../../rc/Pictos_Caps/attaque_test.png");
	capacite_.setTexture(capText_);

	affiche_ = true;
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

void CapBoing::actualiser(std::vector<Projectile*>& projectiles, Entite& vaisseau, float tempsEcoule)
{
	// Pour avoir la création des 4 projectile toute les 5 frames
	if (frames_ < 20 && frames_ % 5 == 0)
	{
		// Création d'un nouveau projectile
		ProjTest *temp = new ProjTest(debutX_, debutY_);
		projectiles.push_back(temp);
	}

	// Si la compétence est en cooldown, on actualise le timer
	if (t_ < cooldown_)
	{
		t_ += tempsEcoule;
	}
	frames_++;
}
