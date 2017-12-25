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

	vit_ = 500;

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
	// TODO Solution temporaire
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

	afficher(window);
}

