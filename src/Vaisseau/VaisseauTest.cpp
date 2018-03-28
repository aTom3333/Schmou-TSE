#include "VaisseauTest.h"
#include <cmath>


VaisseauTest::VaisseauTest(Ecran& ecran) : Vaisseau(ecran) ///constructeur
{
	// Sprites
	sprites_.emplace_back(ecran.getChargeur().getTexture("vaiss.vaisseautest.lapin"));
	for (auto& sprite : sprites_)
		sprite.setOrigin({ this->getTaille().x / 2.0f, this->getTaille().y / 2.0f });

	// Cercle englobant
	//TODO PG Englobeur
	const float largeur_vaisseau = this->getTaille().x;
	const float hauteur_vaisseau = this->getTaille().y;
	const float R = sqrt(2 * largeur_vaisseau * hauteur_vaisseau);
	cercleEnglobant_ = sf::CircleShape((float)R);
	cercleEnglobant_.setOrigin(R, R);
	cercleEnglobant_.setPosition(32, 32);

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

	// Origine
	origine_ = { this->getTaille().x / 2.0f, this->getTaille().y / 2.0f };

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
	regenBOU_ = 0;
	regenPV_ = 0;

	degatsColl_ = 50;

	// Capacités
	std::shared_ptr<VaisseauTest> temp_ptr(this);
	//TODO PG est-ce que cela marche ?!?

	//TIR1 Piou
	capacites_.emplace_back(CapPiou(ecran, std::weak_ptr<VaisseauTest>(temp_ptr)));

	//TIR2 Dash
	capacites_.emplace_back(CapDash(ecran, std::weak_ptr<VaisseauTest>(temp_ptr)));

	//COMP1 BouclierRond
	capacites_.emplace_back(CapBouclierRond(ecran, std::weak_ptr<VaisseauTest>(temp_ptr)));

	//COMP2 Missile
	//TODO PG CapMissile
	//capacites_.emplace_back(CapMissile(ecran, std::weak_ptr<VaisseauTest>(temp_ptr)));

	//COMP3 Boing
	capacites_.emplace_back(CapBoing(ecran, std::weak_ptr<VaisseauTest>(temp_ptr)));

	//ULTI Bismillah
	capacites_.emplace_back(CapBismillah(ecran, std::weak_ptr<VaisseauTest>(temp_ptr)));
}

void VaisseauTest::gestion(proj_container proj_cont, Input& input)
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
		capacites_[3]->utiliser(proj_cont);
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
	last_delta_ = input.move(vit_, ecran_.getClock().getElapsedTime());
	move(last_delta_);

	afficher();
}

