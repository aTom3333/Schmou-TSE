#include <vector>
#include <string>
#include <algorithm>
#include "../Capacites/Capacite.h"
#include "Vaisseau.h"
#include "../Projectiles/Projectile.h"


Vaisseau::Vaisseau() ///constructeur
{
	//personnalisation
	//stats de base
	pvM_ = 100;
	atqM_ = 100;
	defM_ = 100;
	vitM_ = 100;
	//liste de capacités
}


Vaisseau::~Vaisseau() ///destructeur
{
	for (int i = 0; i < capacites_.size(); i++)
		delete capacites_[i];
}

void Vaisseau::gestionCapacite(std::vector <Projectile*> &projectiles, sf::Time t_ecoule)
{
	// Gestion des capacites_
	for (int i = 0; i < capacites_.size(); i++)
		capacites_[i]->actualiser(projectiles, *this, t_ecoule.asMilliseconds());
}


void Vaisseau::setActif(bool val)
{
	actif_ = val;
}

bool Vaisseau::estActif()
{
	return actif_;
}

//setters
	void Vaisseau::setEquipe(int equipe)
	{
		equipe_ = equipe;
	}

	void Vaisseau::addCapacite(Capacite* skill)
	{
		capacites_.push_back(skill);
	}

	void Vaisseau::setnom(std::string nom)
	{
		nom_ = nom;
	}

	void Vaisseau::setNskin(int Nskin)
	{
		Nskin_ = Nskin;
	}

	void Vaisseau::setpvM(int pvM)
	{
		pvM_ = pvM;
	}

	void Vaisseau::setatqM(int atqM)
	{
		atqM = atqM;
	}

	void Vaisseau::setdefM(int defM)
	{
		defM_ = defM;
	}

	void Vaisseau::setvitM(int vitM)
	{
		vitM_ = vitM;
	}

	void Vaisseau::setpv(int pv)
	{
		pv_ = pv;
	}

	void Vaisseau::setatq(int atq)
	{
		atq_ = atq;
	}

	void Vaisseau::setdef(int def)
	{
		def_ = def;
	}

	void Vaisseau::setvit(int vit)
	{
		vit_ = vit;
	}


//getters
	std::string Vaisseau::getnom()
	{
		return nom_;
	}

	int Vaisseau::getNskin()
	{
		return Nskin_;
	}

	int Vaisseau::getpvM()
	{
		return pvM_;
	}

	int Vaisseau::getatqM()
	{
		return atqM_;
	}

	int Vaisseau::getdefM()
	{
		return defM_;
	}

	int Vaisseau::getvitM()
	{
		return vitM_;
	}

	int Vaisseau::getpv()
	{
		return pv_;
	}

	int Vaisseau::getatq()
	{
		return atq_;
	}

	int Vaisseau::getdef()
	{
		return def_;
	}

	int Vaisseau::getvit()
	{
		return vit_;
	}

	std::vector<Capacite*> Vaisseau::getskills()
	{
		return capacites_;
	}
