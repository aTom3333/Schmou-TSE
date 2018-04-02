#include "CapMissile.h"

CapMissile::CapMissile(Ecran& ecran, const std::weak_ptr<Entite>& lanceur):
	Capacite(ecran, lanceur)
{
	//Caractéristiques
	cooldown_ = sf::milliseconds(2000);
	nom_ = "Missile";

	//Sprites
	sprites_.emplace_back(*ecran.getChargeur().getTexture("Cap.missile"));

}

void CapMissile::utiliser(proj_container& projectiles)
{
	if (auto lanceur = lanceur_.lock())
	{
		// Si la compétence est disponible
		if (t_lastuse_ >= cooldown_)
		{
			// Reset timer
			t_lastuse_ = sf::Time::Zero;

			// Création du projectile au lancement
			proj_ptr temp(new ProjMissile(ecran_, lanceur, sprites_, sounds_, lanceur->getEquipe()));
			projectiles.push_back(temp);
		}
	}
}

void CapMissile::actualiser(proj_container& projectiles)
{
	t_lastuse_ += ecran_.getTempsFrame();
}
