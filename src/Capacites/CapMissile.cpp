#include "CapMissile.h"

CapMissile::CapMissile(Ecran& ecran, const std::weak_ptr<Entite>& lanceur):
	Capacite(ecran, lanceur)
{
	//Caractéristiques
	t_lastuse_.restart();
	cooldown_ = sf::milliseconds(100);
	nom_ = "Missile";

	//Sprites
	sprites_.emplace_back(ecran.getChargeur().getTexture("Cap.missile"));

}

void CapMissile::utiliser(proj_container& projectiles)
{
	if (auto lanceur = lanceur_.lock())
	{
		// Si la compétence est disponible
		if (t_lastuse_.getElapsedTime() >= cooldown_)
		{
			// Début du timer
			t_lastuse_.restart();
			// Création du projectile au lancement
			proj_ptr temp(new ProjMissile(ecran_, lanceur, sprites_, sounds_, lanceur->getEquipe()));
			projectiles.push_back(temp);
		}
	}
}

void CapMissile::actualiser(proj_container& projectiles)
{

}
