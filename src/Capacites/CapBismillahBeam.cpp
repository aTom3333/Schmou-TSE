#include "CapBismillahBeam.h"
#include "../Projectiles/ProjBismillah.h"

CapBismillah::CapBismillah()
{
	//Caractéristiques
	t_ = frames_ = cooldown_ = 1000; //ms
	nom_ = "Bismillah";

	//Icône
	capText_.loadFromFile("../../rc/Icones_Caps/laser.png");
	capacite_.setTexture(capText_);
	
	//Texture
	for(size_t i = 0; i < 4; ++i) textureV_.emplace_back(new sf::Texture);//resize de taille 4 avec des unique_ptr sur sf::Texture vides
	textureV_.at(0)->loadFromFile("../../rc/Sprites/Capacites/BismillahBeam/charge92x92.png");
	textureV_.at(1)->loadFromFile("../../rc/Sprites/Capacites/BismillahBeam/base_rayon1.png");
	textureV_.at(2)->loadFromFile("../../rc/Sprites/Capacites/BismillahBeam/base_rayon2.png");
	textureV_.at(3)->loadFromFile("../../rc/Sprites/Capacites/BismillahBeam/base_rayon3.png");
	for(size_t i = 0; i < 4; ++i) spriteV_.emplace_back(sf::Sprite(*textureV_.at(i)));

    //Son
    soundbuffer_.loadFromFile("../../rc/Sounds/Capacites/Bismillah.wav");
    sound_.setBuffer(soundbuffer_);
    sound_.setLoop(false);

    affiche_ = true;
}

void CapBismillah::utiliser(int x, int y)
{
	// Si la compétence est disponible
	if (t_ >= cooldown_)
	{
		// Début du timer
		t_ = 0;
		frames_ = 0;
	}

}

void CapBismillah::actualiser(proj_container& projectiles, Entite& vaisseau, float tempsEcoule)
{
    // Juste pour mute les warnings du compilateur
    (void)vaisseau;

	// Création du projectile au moment où la compétence est lancée
	if (frames_ == 0)
	{
		proj_ptr temp(new ProjBismillah(vaisseau, spriteV_, sound_, JOUEUR));
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