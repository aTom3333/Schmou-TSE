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

	pvMax_ = 300;
	armureMax_ = 100;
	bouclierMax_ = 100;

	pv_ = pvMax_;
	armure_ = armureMax_;
	bouclier_ = bouclierMax_;

	regenARM_ = 0;
	regenBOU_ = 1;
	regenPV_ = 0;

	degats_ = 50;

	actif_ = true;



	// Capacit�s
	CapTest *temp1 = new CapTest();
	capacites_.push_back(temp1);

	CapPiou *temp2 = new CapPiou();
	capacites_.push_back(temp2);

	CapDash *temp3 = new CapDash();
	capacites_.push_back(temp3);

	attaqueEnCours_ = 1;

}

VaisseauTest::~VaisseauTest()///destructeur
{
}

void VaisseauTest::gestion(sf::RenderWindow & window, sf::Time tempsEcoule, Input& input)
{
	// Gestion du vaisseau
	// Si la touche W est activ�
	if (input.action(Tir1))
	{
		// Lance la comp�tance � la position du vaisseau alli�
		sf::Vector2f posVaisseau = position_;
		if(attaqueEnCours_ == 1)
			capacites_[attaqueEnCours_]->utiliser(posVaisseau.x + 32, posVaisseau.y - 20);
		else
			capacites_[attaqueEnCours_]->utiliser(posVaisseau.x + 32, posVaisseau.y + 32);
	}
	// Si la touche X est activ�
	if (input.action(Tir2))
	{
		// Changement d'attaque
		attaqueEnCours_++;
		if (attaqueEnCours_ >= capacites_.size())
			attaqueEnCours_ = 0;
	}
	move(input.move(vit_, tempsEcoule));

	afficher(window);
}

