#include "CapBouclierRond.h"

CapBouclierRond::CapBouclierRond(int niveau, Entite* Entite_liee)
{
	niveau_ = niveau;
	Entite_liee_ = Entite_liee;

	capText_.loadFromFile("../../rc/Icones_Caps/boubou.png");
	capacite_.setTexture(capText_);
	affiche_ = true;
	

	switch (niveau)
	{
	default:
		break;

	case 1:
		cooldown_ = 15000;
		pvM_ = 500;
		degatsColl_ = 50;
		tempsMax_ = 3000;
		break;
	case 2:
		cooldown_ = 10000;
		pvM_ = 1000;
		degatsColl_ = 100;
		tempsMax_ = 5000;
		break;
	}
	nom_ = "Bouclier";
	t_ = cooldown_;
	frames_ = cooldown_; //TODO ici le warning pourrait être important (float vers uint)

}

void CapBouclierRond::utiliser(int x, int y)
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


void CapBouclierRond::actualiser(std::vector<Projectile*>& GVP, Entite& vaisseau, float tempsEcoule)
{
	// Création du projectile au moment où la compétence est lancée
	if (frames_ == 0)
	{
		//TODO bug
		ProjBouclierRond *temp = new ProjBouclierRond(Entite_liee_, pvM_, degatsColl_, tempsMax_, vaisseau.getEquipe());
		GVP.push_back(temp);
	}

	// Si la compétence est en cooldown, on actualise le timer
	if (t_ < cooldown_)
	{
		t_ += tempsEcoule;
	}
	frames_++;
	
}
