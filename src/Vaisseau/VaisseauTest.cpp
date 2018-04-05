#include "VaisseauTest.h"
#include <cmath>


VaisseauTest::VaisseauTest() ///constructeur
{
	//sprite
	texture_.loadFromFile("../../rc/Sprites/base/vaisseauTest.png");
	sprite_.setTexture(texture_);
	sprite_.setOrigin({ 32,52 });

	//cercle englobant
	const float largeur_vaisseau = this->getTaille().x;
	const float hauteur_vaisseau = this->getTaille().y;
	const float R = sqrt(2 * largeur_vaisseau * hauteur_vaisseau);
	cercleEnglobant_ = sf::CircleShape((float)R);
	cercleEnglobant_.setOrigin(R, R);
	cercleEnglobant_.setPosition(32, 32);

	//forme / hitbox constituée de la forme exacte
	sf::ConvexShape forme1(3);
	forme1.setPoint(0, { 0,64 });
	forme1.setPoint(1, { 32,0 });
	forme1.setPoint(2, { 32,46 });
	forme1.setOrigin({ 32, 32 });
	sf::ConvexShape forme2(3);
	forme2.setPoint(0, { 0,0 });
	forme2.setPoint(1, { 32,64 });
	forme2.setPoint(2, { 0,46 });
	forme2.setOrigin({ 0, 32 });

	//origine d'Entite
	origine_ = { 32,32 };

	forme_.emplace_back(new sf::ConvexShape(forme1));
	forme_.emplace_back(new sf::ConvexShape(forme2));


	// Caractéristiques
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
	regenBOU_ = 1;
	regenPV_ = 0;

	degatsColl_ = 50;

	// Capacités

	//TIR1
	CapPiou *piou = new CapPiou();
	capacites_.push_back(piou);

	//TIR2
	CapDash *dash = new CapDash();
	capacites_.push_back(dash);

	//COMP1
	CapBouclierRond *boubou = new CapBouclierRond(1, this);
	capacites_.push_back(boubou);

	//COMP2
	//TODO CapMissile
	capacites_.push_back(nullptr);

	//COMP 3
	CapBoing *boing = new CapBoing();
	capacites_.push_back(boing);

	//ULTI
	CapBismillah *bism = new CapBismillah();
	capacites_.push_back(bism);
}

void VaisseauTest::gestion(sf::RenderWindow & window, sf::Time tempsEcoule, Input& input)
{
	// Gestion du vaisseau
	// Si la touche TIR 1 est activé
	if (input.action(TIR1))
	{
		// Lance la compétence à la position du vaisseau allié
		capacites_[0]->utiliser(position_.x, position_.y);

	}
	// Si la touche TIR 2 est activé
	if (input.action(TIR2))
	{
		// Lance la compétence à la position du vaisseau allié
		capacites_[1]->utiliser(position_.x, position_.y);
	}

	// Si la touche COMP 1 est activé
	if (input.action(COMP1))
	{
		// Lance la compétence à la position du vaisseau allié
		capacites_[2]->utiliser(position_.x, position_.y);
	}

	// Si la touche COMP 2 est activé
	if (input.action(COMP2))
	{
		
	}

	// Si la touche COMP 3 est activé
	if (input.action(COMP3))
	{
		// Lance la compétence à la position du vaisseau allié
		capacites_[4]->utiliser(position_.x, position_.y);
	}

	// Si la touche ULTI est activé
	if (input.action(ULTI))
	{
		capacites_[5]->utiliser(position_.x, position_.y);
	}

	//déplacement
	last_delta_ = input.move(vit_, tempsEcoule);
	move(last_delta_);

	afficher(window);
}

