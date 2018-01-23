﻿#include "VaisseauTest.h"

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
	armureMax_ = 100;
	bouclierMax_ = 0;

	pv_ = pvMax_;
	armure_ = armureMax_;
	bouclier_ = bouclierMax_;

	regenARM_ = 0;
	regenBOU_ = 1;
	regenPV_ = 0;

	degatsColl_ = 50;

	actif_ = true;



	// Capacités
	CapBouclierRond *temp1 = new CapBouclierRond(1, this);
	capacites_.push_back(temp1);

	CapTest *temp2 = new CapTest();
	capacites_.push_back(temp2);

	CapPiou *temp3 = new CapPiou();
	capacites_.push_back(temp3);

	CapDash *temp4 = new CapDash();
	capacites_.push_back(temp4);



	attaqueEnCours_ = 1;

}

VaisseauTest::~VaisseauTest()///destructeur
{
}

void VaisseauTest::gestion(sf::RenderWindow & window, sf::Time tempsEcoule, Input input)
{
	// Gestion du vaisseau
	// Si la touche W est activé
	if (input.action(0))
	{
		// Lance la compétence à la position du vaisseau allié
		sf::Vector2f posVaisseau = position_;
		if(attaqueEnCours_ == 1)
			capacites_[attaqueEnCours_]->utiliser(posVaisseau.x + 32, posVaisseau.y - 20);
		else
			capacites_[attaqueEnCours_]->utiliser(posVaisseau.x + 32, posVaisseau.y + 32);
	}
	// Si la touche X est activé
	if (input.action(1))
	{
		// Changement d'attaque
		attaqueEnCours_++;
		if (attaqueEnCours_ >= capacites_.size())
			attaqueEnCours_ = 0;
	}
	move(input.move(vit_, tempsEcoule));

	// Affichage des informations sur la capacité en cours
	// TODO A mettre dans la classe affichant l'interface
		sf::Text afficheAtk;
		sf::Font font_;
		font_.loadFromFile("../../rc/Font/hemi.ttf");
		// Initialisation du texte (Nom capacité + Cooldown)
		afficheAtk.setFont(font_);
		afficheAtk.setCharacterSize(20);
		afficheAtk.setFillColor(sf::Color::White);
		afficheAtk.setPosition(0, 0);

		std::string txt;
		if (capacites_[attaqueEnCours_]->getCooldown() - capacites_[attaqueEnCours_]->getTime() > 0)
			txt = capacites_[attaqueEnCours_]->getNom() + " - " + std::to_string((int)(capacites_[attaqueEnCours_]->getCooldown() - capacites_[attaqueEnCours_]->getTime()));
		else
			txt = capacites_[attaqueEnCours_]->getNom() + " - " + "Pret";
		afficheAtk.setString(txt);
		window.draw(afficheAtk);

	// Affichage des points de vie/bouclier/armure
	// TODO A mettre dans la classe affichant l'interface
		sf::RectangleShape rec;
		sf::Vector2f size;

		// PV
		size.x = pv_/pvMax_ * 300;
		size.y = 30;
		rec.setSize(size);
		rec.setPosition(0, 30);
		rec.setFillColor(sf::Color::Green);
		window.draw(rec);

		// Armure
		size.x = armure_ / armureMax_ * 200;
		size.y = 20;
		rec.setSize(size);
		rec.setPosition(0, 60);
		rec.setFillColor(sf::Color::Yellow);
		window.draw(rec);

		// Bouclier
		size.x = bouclier_ / bouclierMax_ * 200;
		size.y = 20;
		rec.setSize(size);
		rec.setPosition(0, 80);
		rec.setFillColor(sf::Color::Blue);
		window.draw(rec);

	afficher(window);
}

