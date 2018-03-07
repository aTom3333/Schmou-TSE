#include "VaisseauTest.h"
#include <cmath>


VaisseauTest::VaisseauTest() ///constructeur
{
	//sprite
	texture_.loadFromFile("../../rc/Sprites/base/vaisseauNoel.png");
	sprite_.setTexture(texture_);

	//hitbox simple
	cercleEnglobant_ = sf::CircleShape(sqrt(2*32*32));
	cercleEnglobant_.setOrigin(sqrt(2 * 32 * 32), sqrt(2 * 32 * 32));
	cercleEnglobant_.setPosition(32, 32);
	forme_.emplace_back(new sf::CircleShape(cercleEnglobant_));

	// Stats
	vit_ = 500;

	pvMax_ = 1000;
	armureMax_ = 50;
	bouclierMax_ = 100;

	pv_ = pvMax_;
	armure_ = armureMax_;
	bouclier_ = bouclierMax_;

	regenARM_ = 0;
	regenBOU_ = 1;
	regenPV_ = 0;

	degats_ = 50;

	actif_ = true;



	// Capacités

	//rien en pos 0
	capacites_.push_back(nullptr);

	//TIR1
	CapPiou *temp1 = new CapPiou();
	capacites_.push_back(temp1);

	//TIR2
	//TODO CapMissile
	capacites_.push_back(nullptr);

	//COMP1
	CapBouclierRond *temp3 = new CapBouclierRond(1, this);
	capacites_.push_back(temp3);

	//COMP2
	CapDash *temp4 = new CapDash();
	capacites_.push_back(temp4);

	//COMP 3
	CapBoing *temp5 = new CapBoing();
	capacites_.push_back(temp5);

	//ULTI
	//TODO CapBismillahBeam

	attaqueEnCours_ = 1;

}

VaisseauTest::~VaisseauTest()///destructeur
{
}

void VaisseauTest::gestion(sf::RenderWindow & window, sf::Time tempsEcoule, Input& input)
{
	// Gestion du vaisseau
	// Si la touche TIR 1 est activé
	if (input.action(TIR1))
	{
		// Lance la compétence à la position du vaisseau allié
		sf::Vector2f posVaisseau = position_;
		capacites_[1]->utiliser(posVaisseau.x + 32, posVaisseau.y - 20);

	}
	// Si la touche TIR 2 est activé
	if (input.action(TIR2))
	{
		
	}

	// Si la touche COMP 1 est activé
	if (input.action(COMP1))
	{
		// Lance la compétence à la position du vaisseau allié
		sf::Vector2f posVaisseau = position_;
		capacites_[3]->utiliser(posVaisseau.x + 32, posVaisseau.y + 32);
	}

	// Si la touche COMP 2 est activé
	if (input.action(COMP2))
	{
		// Lance la compétence à la position du vaisseau allié
		sf::Vector2f posVaisseau = position_;
		capacites_[4]->utiliser(posVaisseau.x + 32, posVaisseau.y + 32);
	}

	// Si la touche COMP 3 est activé
	if (input.action(COMP3))
	{
		// Lance la compétence à la position du vaisseau allié
		sf::Vector2f posVaisseau = position_;
		capacites_[5]->utiliser(posVaisseau.x + 32, posVaisseau.y + 32);
	}

	// Si la touche ULTI est activé
	if (input.action(ULTI))
	{
	}





	//déplacement
	move(input.move(vit_, tempsEcoule));

	afficher(window);
}

