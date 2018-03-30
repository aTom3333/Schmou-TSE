#include "CapBouclierRond.h"

CapBouclierRond::CapBouclierRond(Ecran& ecran, const std::weak_ptr<Entite>& lanceur) :
	Capacite(ecran, lanceur)
{
	//Caractéristiques
	cooldown_ = sf::milliseconds(10000);
	nom_ = "Bouclier";

	//Icônes
	icone_.setTexture(*ecran.getChargeur().getTexture("icone.boubou"));
	afficheIcone_ = true;

	//Sprites
	sprites_.emplace_back(*ecran.getChargeur().getTexture("Cap.boubou"));

	//Son
	sounds_.emplace_back(*ecran.getChargeur().getSoundBuffer("son.boubou"));
	sounds_.front().setLoop(true);

	// TODO CL Gestion des niveaux à refaire
	niveau_ = 0;
	//switch (niveau_)
	//{
	//	default:
	//		break;
	//	case 1:
	//		pvM_ = 500;
	//		degatsColl_ = sf::milliseconds(50);
	//		t_longevite_ = 3000;
	//		break;
	//	case 2:
	//		pvM_ = 1000;
	//		degatsColl_ = 100;
	//		t_longevite_ = 5000;
	//		break;
	//}

	//TODO PG structure statistiques !!
}

void CapBouclierRond::utiliser(proj_container& projectiles)
{
	if (auto lanceur = lanceur_.lock())
	{
		// Si la compétence est disponible
		if (t_lastuse_ >= cooldown_)
		{
			// Reset timer
			t_lastuse_ = sf::Time::Zero;

			// Création du projectile au lancement
			proj_ptr temp(new ProjBouclierRond(ecran_, lanceur, sprites_, sounds_, lanceur->getEquipe()));
			projectiles.push_back(temp);
		}
	}
}


void CapBouclierRond::actualiser(proj_container &proj)
{
	t_lastuse_ += ecran_.getTempsFrame();
}
