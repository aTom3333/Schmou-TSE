#include "Vague.h"

Vague::Vague(Ecran& ecran, const sf::Time& t) :
	ecran_{ecran}, t_depart_{t}
{}

void Vague::gestion(vaisseau_container& vaisseaux) //TODO CL ajouter proj_containes au cas où l'élément c'est un proj
{
	t_depuis_debut_partie_ += ecran_.getTempsFrame();
	if (t_depuis_debut_partie_ >= t_depart_ )
	{
		for(size_t i = 0; i < vaisseaux_vague_.size(); i++)
		{
			if (!vaisseaux_vague_[i].actif && vaisseaux_vague_[i].t_depart_element < t_depuis_debut_partie_ - t_depart_)
			{
				vaisseaux_vague_[i].actif = true;
				vaisseaux_vague_[i].v->setActif(true);
				vaisseaux.push_back(vaisseaux_vague_[i].v);
			}
		}
	}
}

