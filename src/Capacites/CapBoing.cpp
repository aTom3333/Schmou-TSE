#include "CapBoing.h"
#include "CapDash.h"

CapBoing::CapBoing(Ecran& ecran, const std::weak_ptr<Entite>& lanceur):
	Capacite(ecran, lanceur)
{
	//Caractéristiques
	cooldown_ = sf::milliseconds(100);
	nom_ = "Boing";
	afficheIcone_ = true;

	//Icônes
	icone_.setTexture(*ecran.getChargeur().getTexture("icone.boing"));

	//Sprites
	sprites_.emplace_back(*ecran.getChargeur().getTexture("Cap.Boing.Paques"));

	//Son
	sounds_.emplace_back(*ecran.getChargeur().getSoundBuffer("son.boing"));
	sounds_.front().setLoop(false);

}



void CapBoing::utiliser(proj_container& projectiles)
{
	if (auto lanceur = lanceur_.lock())
	{
		// Si la compétence est disponible
		if (t_lastuse_ >= cooldown_)
		{
			// Reset timer
			t_lastuse_ = sf::Time::Zero;

			for (int i = 0; i < 5; i++)
			{
				// Initialisation de l'endroit ou la compétence a été utilisée
				proj_ptr temp(new ProjBoing(ecran_, lanceur, sprites_, sounds_, lanceur->getEquipe()));
				projectiles.push_back(temp);
			}
		}
	}
}

void CapBoing::actualiser(proj_container& projectiles)
{	
	t_lastuse_ += ecran_.getTempsFrame();
}
