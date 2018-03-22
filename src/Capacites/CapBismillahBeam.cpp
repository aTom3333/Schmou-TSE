#include "CapBismillahBeam.h"
#include "../Projectiles/ProjBismillah.h"

CapBismillah::CapBismillah()
{
	//Caract�ristiques
	t_ = frames_ = cooldown_ = 1000; //ms

	//TODO PG ici le warning pourrait �tre important (frames_ : float vers uint)
	nom_ = "Bismillah";

	//Ic�ne
	capText_.loadFromFile("../../rc/Icones_Caps/laser.png");
	capacite_.setTexture(capText_);
	
	//Texture
	for (size_t i = 0; i < 4; ++i) textureV_.emplace_back(std::unique_ptr<sf::Texture>(new sf::Texture));//resize de taille 4 avec des unique_ptr sur sf::Texture vides
	textureV_.at(0).get()->loadFromFile("../../rc/Sprites/Capacites/BismillahBeam/charge.png");
	textureV_.at(1).get()->loadFromFile("../../rc/Sprites/Capacites/BismillahBeam/base_rayon1.png");
	textureV_.at(2).get()->loadFromFile("../../rc/Sprites/Capacites/BismillahBeam/base_rayon2.png");
	textureV_.at(3).get()->loadFromFile("../../rc/Sprites/Capacites/BismillahBeam/base_rayon3.png");
	for (size_t i = 0; i < 4; ++i) spriteV_.emplace_back(sf::Sprite(*textureV_.at(i).get()));

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
		// D�but du timer
		t_ = 0;
		frames_ = 0;
	}

}

void CapBismillah::actualiser(proj_container& projectiles, Entite& vaisseau, float tempsEcoule)
{
	// Juste pour mute les warnings du compilateur
    (void)vaisseau;

	// Cr�ation du projectile au moment o� la comp�tence est lanc�e
	if (frames_ == 0)
	{
		//TODO bug
		proj_ptr temp(new ProjBismillah(vaisseau, spriteV_, sound_, ALLIE));
		sound_.play();
		projectiles.push_back(temp);
	}

	// Si la comp�tence est en cooldown, on actualise le timer
	if (t_ < cooldown_)
	{
		t_ += tempsEcoule;
		frames_++;
	}
}