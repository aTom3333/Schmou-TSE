#ifndef ECRAN_ACCEUIL_H
#define ECRAN_ACCEUIL_H

#include "Ecran.h"

class Accueil : public Ecran
{
public:
	Accueil(sf::RenderWindow& window) : Ecran(window) {};
	~Accueil() {};

	ecran_t executer() override;

	std::unique_ptr<Ecran> factory() override;

private:
};

#endif // !ECRAN_ACCEUIL_H

