#include "VaisseauTest.h"
#include <cmath>


VaisseauTest::VaisseauTest(Ecran& ecran) : Vaisseau(ecran) ///constructeur
{
	// Sprites
	sprites_.emplace_back(*ecran.getChargeur().getTexture("vaiss.vaisseautest.lapin"));
	for (auto& sprite : sprites_)
		sprite.setOrigin({ this->getTaille().x / 2.0f, this->getTaille().y / 2.0f });

	// Origine
	origine_ = { this->getTaille().x / 2.0f, this->getTaille().y / 2.0f };

	// Sons
	sounds_.emplace_back(*ecran.getChargeur().getSoundBuffer("son.sakado"));

	// Cercle englobant
	//TODO PG Englobeur
	const float largeur_vaisseau = this->getTaille().x;
	const float hauteur_vaisseau = this->getTaille().y;
	const float R = hypot(largeur_vaisseau / 2.0f, hauteur_vaisseau / 2.0f);
	cercleEnglobant_ = sf::CircleShape(R);
	cercleEnglobant_.setOrigin(R, R);
	cercleEnglobant_.setPosition({ 0,0 });

	// Hitbox
	sf::ConvexShape forme1(3);
	forme1.setPoint(0, { 0,64 });
	forme1.setPoint(1, { 32,0 });
	forme1.setPoint(2, { 32,46 });
	forme1.setOrigin({ 32, 32 });
	forme_.emplace_back(new sf::ConvexShape(forme1));

	sf::ConvexShape forme2(3);
	forme2.setPoint(0, { 0,0 });
	forme2.setPoint(1, { 32,64 });
	forme2.setPoint(2, { 0,46 });
	forme2.setOrigin({ 0, 32 });
	forme_.emplace_back(new sf::ConvexShape(forme2));

	// Caractéristiques de code
	equipe_ = JOUEUR;
	innate_ = true;
	actif_ = true;
	nbPositions_ = 0;

	// Stats
	pv_ = pvM_ = 1000;
	armure_ = armureM_ = 50;
	bouclier_ = bouclierM_ = 100;
	vit_ = vitM_ = 500;

	regenARM_ = 0;
	regenBOU_ = 5;
	regenPV_ = 0;

	degatsColl_ = 50;
}

void VaisseauTest::gestion(proj_container& proj_cont, Input& input)
{
	// Gestion du vaisseau
	// Si la touche TIR 1 est activé
	if (input.action(TIR1))
	{
		capacites_[0]->utiliser(proj_cont);

	}
	// Si la touche TIR 2 est activé
	if (input.action(TIR2))
	{
		capacites_[1]->utiliser(proj_cont);
	}

	// Si la touche COMP 1 est activé
	if (input.action(COMP1))
	{
		capacites_[2]->utiliser(proj_cont);
	}

	// Si la touche COMP 2 est activé
	if (input.action(COMP2))
	{
		//TODO PG Missile
		//capacites_[3]->utiliser(proj_cont);
	}

	// Si la touche COMP 3 est activé
	if (input.action(COMP3))
	{
		capacites_[4]->utiliser(proj_cont);
	}

	// Si la touche ULTI est activé
	if (input.action(ULTI))
	{
		capacites_[5]->utiliser(proj_cont);
	}

	//déplacement
	last_delta_ = input.move(vit_, ecran_.getTempsFrame());
	move(last_delta_);

	afficher();
}

