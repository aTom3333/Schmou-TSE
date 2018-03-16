#include "CapBismillahBeam.h"
#include "../Projectiles/ProjBismillah.h"

CapBismillah::CapBismillah()
{
	//Caract�ristiques
	t_ = frames_ = cooldown_ = 1000;
	//TODO ici le warning pourrait �tre important (frames_ : float vers uint)
	nom_ = "Bismillah";

	//Ic�ne
	capText_.loadFromFile("../../rc/Icones_Caps/laser.png");
	capacite_.setTexture(capText_);

	//Son
	soundbuffer_.loadFromFile("../../rc/Sounds/Capacites/Bismillah.wav");
	sound_.setBuffer(soundbuffer_);
	sound_.setLoop(false);

	affiche_ = true;
}

void CapBismillah::utiliser(int x, int y)
{
	// Si la comp�tence est disponible
	if (t_ >= cooldown_)
	{
		//Son au lancement
		sound_.play();
		// D�but du timer
		t_ = 0;
		frames_ = 0;
		// Initialisation de l'endroit ou la comp�tence a �t� utilis�e
		debutX_ = x;
		debutY_ = y;
	}

}

void CapBismillah::actualiser(proj_container& projectiles, Entite& vaisseau, float tempsEcoule)
{
	// Cr�ation du projectile au moment o� la comp�tence est lanc�e
	if (frames_ == 0)
	{
		//TODO bug
		proj_ptr temp(new ProjBismillah(debutX_, debutY_, sound_, ALLIE));
		projectiles.push_back(temp);
	}

	// Si la comp�tence est en cooldown, on actualise le timer
	if (t_ < cooldown_)
	{
		t_ += tempsEcoule;
		frames_++;

	}

}