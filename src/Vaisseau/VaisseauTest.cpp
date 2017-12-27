#include "VaisseauTest.h"


VaisseauTest::VaisseauTest() ///constructeur
{
	//sprite
	texture_.loadFromFile("../../rc/Sprites/base/vaisseauNoel.png");
	sprite_.setTexture(texture_);

	//hitbox simple
	cercleEnglobant_ = sf::CircleShape(32);
	cercleEnglobant_.setOrigin(32, 32);
	cercleEnglobant_.setPosition(32, 32);
	forme_.emplace_back(new sf::CircleShape(cercleEnglobant_));

	// Stats
	vit_ = 500;

	pvMax_ = 300;
	armureMax_ = 200;
	bouclierMax_ = 250;

	pv_ = pvMax_;
	armure_ = armureMax_;
	bouclier_ = bouclierMax_;

	regenARM_ = 0;
	regenBOU_ = 2;
	regenPV_ = 0;

	degats_ = 50;


	// Capacités
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

void VaisseauTest::gestion(sf::RenderWindow & window, sf::Time tempsEcoule, Input input)
{
	// Gestion du vaisseau
	// Si la touche W est activé
	if (input.action(0))
	{
		// Lance la compétance à la position du vaisseau allié
		sf::Vector2f posVaisseau = position_;
		capacites_[attaqueEnCours_]->utiliser(posVaisseau.x, posVaisseau.y);
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

