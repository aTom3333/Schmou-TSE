#include "CapBismillahBeam.h"
#include "../Projectiles/ProjBismillah.h"

CapBismillah::CapBismillah(Ecran& ecran, const std::weak_ptr<Entite>& lanceur) :
	Capacite(ecran, lanceur)
{
	//Caractéristiques
	cooldown_ = sf::milliseconds(200);
	nom_ = "Bismillah";

	//Icône
	icone_.setTexture(*ecran.getChargeur().getTexture("icone.bism"));
	afficheIcone_ = true;
	
	//Sprites
	sprites_.emplace_back(*ecran.getChargeur().getTexture("cap.bism.charge"));
	sprites_.emplace_back(*ecran.getChargeur().getTexture("cap.bism.rayon",true)); //texture du rayon est répétée

    //Sons
    sounds_.emplace_back(*ecran.getChargeur().getSoundBuffer("son.bism"));
}

void CapBismillah::utiliser(proj_container& projectiles)
{
	if (auto lanceur = lanceur_.lock())
	{
		// Si la compétence est disponible
		if (t_lastuse_ >= cooldown_)
		{
			// Reset timer
			t_lastuse_ = sf::Time::Zero;

			// Création du projectile au lancement
			proj_ptr temp(new ProjBismillah(ecran_, lanceur, sprites_, sounds_, lanceur->getEquipe()));
			projectiles.push_back(temp);
		}
	}
}

void CapBismillah::actualiser(proj_container& projectiles)
{
	t_lastuse_ += ecran_.getTempsFrame();
}