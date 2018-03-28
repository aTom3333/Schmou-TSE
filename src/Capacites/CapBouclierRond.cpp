﻿#include "CapBouclierRond.h"

CapBouclierRond::CapBouclierRond(Ecran& ecran, const std::weak_ptr<Entite>& lanceur) :
	Capacite(ecran, lanceur)
{
	//Caractéristiques
	t_lastuse_.restart();
	cooldown_ = sf::milliseconds(100);
	nom_ = "Bouclier";

	//Icônes
	capacite_.setTexture(*ecran.getChargeur().getTexture("icone.boubou"));
	affiche_ = true;

	//Sprites
	sprites_.emplace_back(ecran.getChargeur().getTexture("Cap.boubou"));

	//Son
	sounds_.emplace_back(ecran.getChargeur().getSoundBuffer("son.boubou"));
	sounds_.front().setLoop(true);

	// TODO CL Gestion des niveaux à refaire
	switch (niveau)
	{
		default:
			break;
		case 1:
			cooldown_ = 15000;
			pvM_ = 500;
			degatsColl_ = 50;
			tempsMax_ = 3000;
			break;
		case 2:
			cooldown_ = 10000;
			pvM_ = 1000;
			degatsColl_ = 100;
			tempsMax_ = 5000;
			break;
	}

void CapBouclierRond::utiliser(proj_container& projectiles)
{
	if (auto lanceur = lanceur_.lock())
	{
		// Si la compétence est disponible
		if (t_lastuse_.getElapsedTime() >= cooldown_)
		{
			// Début du timer
			t_lastuse_.restart();
			// Création du projectile au lancement
			proj_ptr temp(new ProjBouclierRond(ecran_, lanceur, sprites_, sounds_, lanceur->getEquipe()));
			projectiles.push_back(temp);

			// Son au lancement
			sounds_.front().play();
		}
	}
}


void CapBouclierRond::actualiser(proj_container& projectiles)
{
	// Juste pour mute les warnings du compilateur
	(void)projectiles;

	// Rien à faire ici
}
