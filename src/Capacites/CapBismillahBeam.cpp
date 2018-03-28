#include "CapBismillahBeam.h"
#include "../Projectiles/ProjBismillah.h"

CapBismillah::CapBismillah(Ecran& ecran, const std::weak_ptr<Entite>& lanceur) :
	Capacite(ecran, lanceur)
{
	//Caractéristiques
	t_lastuse_.restart();
	cooldown_ = sf::milliseconds(20000);
	nom_ = "Bismillah";

	//Icône
	icone_.setTexture(*ecran.getChargeur().getTexture("icone.bism"));
	afficheIcone_ = true;
	
	//Sprites
	sprites_.emplace_back(ecran.getChargeur().getTexture("cap.bism.charge"));
	sprites_.emplace_back(ecran.getChargeur().getTexture("cap.bism.rayon3",true)); //texture du rayon est répétée

    //Sons
    sounds_.emplace_back(ecran.getChargeur().getSoundBuffer("son.bism"));
}

void CapBismillah::utiliser(proj_container& projectiles)
{
	if (auto lanceur = lanceur_.lock())
	{
		// Si la compétence est disponible
		if (t_lastuse_.getElapsedTime() >= cooldown_)
		{
			// Début du timer
			t_lastuse_.restart();
			// Création du projectile au lancement
			proj_ptr temp(new ProjBismillah(ecran_, lanceur, sprites_, sounds_, lanceur->getEquipe()));
			projectiles.push_back(temp);

			// Son au lancement
			sounds_.front().play();
		}
	}
}

void CapBismillah::actualiser()
{
	// Rien à faire pour cette capacité
}