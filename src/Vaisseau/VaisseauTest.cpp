#include "VaisseauTest.h"
#include "../Utilitaires/utilities.h"


VaisseauTest::VaisseauTest(Ecran& ecran) : Vaisseau(ecran) ///constructeur
{
	// Sprites
	sprites_.emplace_back(*ecran.getChargeur().getTexture("vaiss.vaisseautest.deux"));
	for (auto& sprite : sprites_)
		sprite.setOrigin({this->getTailleSprite().x / 2.0f, this->getTailleSprite().y / 2.0f});

	// Origine
	origine_ = { this->getTailleSprite().x / 2.0f, this->getTailleSprite().y / 2.0f };

	// Sons
	sounds_.emplace_back(*ecran.getChargeur().getSoundBuffer("son.sakado"));

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

	// Cercle englobant
	//TODO PG Englobeur
	////const float largeur_vaisseau = this->getTailleSprite().x;
	////const float hauteur_vaisseau = this->getTailleSprite().y;
	////const float R = hypot(largeur_vaisseau / 2.0f, hauteur_vaisseau / 2.0f);
	////const float rayon = rayon_englobeur(forme_, origine_);
	////cercleEnglobant_ = sf::CircleShape(R);
	////cercleEnglobant_.setOrigin(R, R);
	////cercleEnglobant_.setPosition({ 0,0 });
	englobeur_circulaire(*this);

	// Caractéristiques de code
	equipe_ = JOUEUR;
	innate_ = true;
	actif_ = true;
	invincibilable_ = true;

	// Stats
	nom_ = "Vaisseau Test";
	pv_ = pvM_ = 1;
	armure_ = armureM_ = 1;
	bouclier_ = bouclierM_ = 0;
	vit_ = vitM_ = 500;

	regenArmure_ = 0;
	regenBouclier_ = 0;
	regenPv_ = 0;

	degatsCollision_ = 50;

	// Modules
	spriteHangar_.setTexture(*ecran.getChargeur().getTexture("modele.basique"));

	modules_.emplace_back(ecran, DEFENSE, 160, 20);
	modules_.emplace_back(ecran, UTILITAIRE, 160, 100);
	modules_.emplace_back(ecran, UTILITAIRE, 70, 170);
	modules_.emplace_back(ecran, ATTAQUE, 250, 170);
	modules_.emplace_back(ecran, DEPLACEMENT, 160, 200);

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
    last_delta_ = input.move(vit_, ecran_.getTempsFrame(), position_);
	move(last_delta_);

	afficher();
}

void VaisseauTest::destruction()
{
	ecran_.getChargeur().playSoundAtDeath("son.sakado");
	ecran_.setAfficheHUD(false);
	detruit_ = true;
}

