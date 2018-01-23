#include "vague.h"

Vague::Vague()
{
}

Vague::Vague(float t)
{
	t_debut_ = t;
}

Vague::~Vague()
{
	/*for (int i = 0; i < v_.size(); i++)
		delete v_[i].v;*/
}

void Vague::ajouterVaisseau(float t, Vaisseau * v)
{
	v_.push_back({ t, v, false });
}

void Vague::gestion(std::vector<Vaisseau*>& vaisseaux, sf::Time t)
{
	float temps = t.asMilliseconds();
	t_ += temps;
	if (t_ >= t_debut_)
	{
		for (int i = 0; i < v_.size(); i++)
		{
			if (!v_[i].active && v_[i].t < t_ - t_debut_)
			{
				v_[i].active = true;
				v_[i].v->setActif(true);
				vaisseaux.push_back(v_[i].v);
			}
		}
	}
}

void Vague::setTempsDebut(float t)
{
	t_debut_ = t;
}

