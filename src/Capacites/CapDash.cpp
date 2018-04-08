#include "CapDash.h"
#include "../Interface/Input.h"

CapDash::CapDash(Ecran& ecran, const std::weak_ptr<Entite>& lanceur):
	Capacite(ecran, lanceur)
{
	//Caractéristiques
	cooldown_ = sf::milliseconds(1000);
	nom_ = "Dash";

	//Icône
	icone_.setTexture(*ecran.getChargeur().getTexture("icone.dash"));
	tir_ = true;

	//Sons
	sounds_.emplace_back(*ecran.getChargeur().getSoundBuffer("son.dash"));
	sounds_.front().setLoop(false);

	// Trainée
	smoke_ = *ecran.getChargeur().getTexture("vaiss.vaisseautest.deux");

	active_ = false;
}


void CapDash::utiliser(proj_container& projectiles)
{
	if (auto lanceur = lanceur_.lock())
	{
		// Si la compétence est disponible
		if (t_lastuse_ >= cooldown_)
		{
			// Reset timer
			t_lastuse_ = sf::Time::Zero;

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

		if (!active_ && t_lastuse_.asMilliseconds() < 50)
		{
			lanceur->changeSpeed(5000);
			lanceur->setNbPositions(15);
			lanceur->setSmokeTexture(smoke_, { 180, 180, 180 });
			active_ = true;
		}

		if (active_ && t_lastuse_.asMilliseconds() > 50)
		{
			lanceur->changeSpeed(-5000);
			lanceur->setNbPositions(0);
			active_ = false;
		}
		t_lastuse_ += ecran_.getTempsFrame();
	}
}
