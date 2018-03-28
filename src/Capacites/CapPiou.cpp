#include "CapPiou.h"

CapPiou::CapPiou(Ecran& ecran, const std::weak_ptr<Entite>& lanceur) :
	Capacite(ecran, lanceur)
{
	//Caractéristiques
    t_lastuse_.restart();
	cooldown_ = sf::milliseconds(100);
	nom_ = "Canon Laser";

	//Icône
	icone_.setTexture(*ecran.getChargeur().getTexture("icone.tir"));
	tir_ = true;

	//Sprites
	sprites_.emplace_back(ecran.getChargeur().getTexture("Cap.Piou.20x30"));

	//Sons
	sounds_.emplace_back(ecran.getChargeur().getSoundBuffer("son.piou"));
	sounds_.front().setLoop(false);

}


void CapPiou::utiliser(proj_container& projectiles)
{
    if(auto lanceur = lanceur_.lock())
    {
        // Si la compétence est disponible
        if(t_lastuse_.getElapsedTime() >= cooldown_)
        {
            // Début du timer
            t_lastuse_.restart();
            // Création du projectile au lancement
            proj_ptr temp(new ProjPiou(ecran_, lanceur, sprites_, sounds_, lanceur->getEquipe()));
            projectiles.push_back(temp);
            
            // Son au lancement
            sounds_.front().play();
        }
    }
}

void CapPiou::actualiser(proj_container& projectiles)
{    
    // Rien à faire pour cette capacité
}
