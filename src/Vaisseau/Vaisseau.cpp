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
	for(unsigned int i = 0; i < capacites_.size(); i++)
		delete capacites_[i];
}

void Vaisseau::gestionCapacite(std::vector <Projectile*> &projectiles, sf::Time t_ecoule)
{
	// Gestion des capacites_
	for(unsigned int i = 0; i < capacites_.size(); i++)
		if (capacites_[i] != nullptr) capacites_[i]->actualiser(projectiles, *this, (float)t_ecoule.asMilliseconds());
}


void Vaisseau::setActif(bool val)
{
	actif_ = val;
}

void Vaisseau::setAnnexeB(int ind, bool val)
{
	annexesB_[ind] = val;
}

bool Vaisseau::estActif()
{
	return actif_;
}

std::vector<Vaisseau*> Vaisseau::getAnnexes()
{
	return annexes_;
}

std::vector<bool> Vaisseau::getAnnexesB()
{
	return annexesB_;
}

void Vaisseau::agit(Entite & e)
{
	e.recoitDegats(degats_);
	recoitDegats(e.getDegats());
}

//setters
	void Vaisseau::setEquipe(Equipe equipe)
	{
		equipe_ = equipe;
	}

	void Vaisseau::addCapacite(Capacite* skill)
	{
		capacites_.push_back(skill);
	}

	void Vaisseau::setCapacite(Capacite * skill, int n)
	{
		capacites_[n] = skill;
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

	std::vector<Capacite*> Vaisseau::getskills()
	{
		return capacites_;
	}
