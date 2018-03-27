#include "CapPiou.h"

CapPiou::CapPiou(Ecran& ecran, const std::weak_ptr<Entite>& lanceur) :
	Capacite(ecran, lanceur)
{
	//Caractéristiques
    t_lastuse_.restart();
	cooldown_ = sf::milliseconds(100);
	nom_ = "Canon Laser";

	//Icônes
	capTexture_ = ecran.getChargeur().getTexture("icone.tir");
	capacite_.setTexture(*capTexture_);
	tir_ = true;

	//Textures
	sprites_.emplace_back(ecran.getChargeur().getTexture("Cap.Piou.20x30"));

	//Son
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
            // Initialisation de l'endroit ou la compétence a été utilisée
            proj_ptr temp(new ProjPiou(ecran_, lanceur, sprites_, sounds_, lanceur->getEquipe()));
            projectiles.push_back(temp);
            
            // Son au lancement
            sounds_.front().play();
        }
    }
}

void CapPiou::actualiser(proj_container& projectiles)
{
    // Juste pour mute les warnings du compilateur
    (void)projectiles;
    
    // Rien à faire ici
}
