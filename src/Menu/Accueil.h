#ifndef ECRAN_ACCEUIL_H
#define ECRAN_ACCEUIL_H

#include "Ecran.h"

class Accueil : public Ecran
{
public:
    explicit Accueil(sf::RenderWindow& window);
	~Accueil() {};

	ecran_t executer(std::vector<std::unique_ptr<Ecran>>& vectEtats, sf::Texture &derniereFenetre) override;

	std::unique_ptr<Ecran> factory() override;

private:
	sf::Texture fondText_;
	sf::Sprite fond_;
	sf::Text texte_;
};

#endif // !ECRAN_ACCEUIL_H

