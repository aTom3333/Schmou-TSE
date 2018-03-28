#include "CapDash.h"
#include "../Interface/Input.h"

CapDash::CapDash(Ecran& ecran, const std::weak_ptr<Entite>& lanceur):
	Capacite(ecran, lanceur)
{
	//Caractéristiques
	t_lastuse_.restart();
	cooldown_ = sf::milliseconds(100);
	nom_ = "Dash";

	//Icône
	icone_.setTexture(*ecran.getChargeur().getTexture("icone.dash"));
	tir_ = true;

	//Sprites
	sprites_.emplace_back(ecran.getChargeur().getTexture("Cap.Dash"));

	//Sons
	sounds_.emplace_back(ecran.getChargeur().getSoundBuffer("son.dash"));
	sounds_.front().setLoop(false);

	active_ = false;
}


void CapDash::utiliser(proj_container& projectiles)
{
	if (auto lanceur = lanceur_.lock())
	{
		// Si la compétence est disponible
		if (t_lastuse_.getElapsedTime() >= cooldown_)
		{
			// Début du timer
			t_lastuse_.restart();

			// Son au lancement
			sounds_.front().play();
		}
	}
}


void CapDash::actualiser(proj_container& projectiles)
{	
	//TODO PG weak_ptr est-ce propre ?
	assert(!lanceur_.expired());
	if (auto lanceur = lanceur_.lock()) {

		if (!active_ && t_lastuse_.getElapsedTime().asMilliseconds() < 100)
		{
			lanceur->changeSpeed(5000);
			active_ = true;
		}

		if (active_ && t_lastuse_.getElapsedTime().asMilliseconds() > 100)
		{
			lanceur->changeSpeed(-5000);
			active_ = false;
		}
	}
}
