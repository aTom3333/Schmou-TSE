#ifndef MENU_PRINCIPAL_H
#define MENU_PRINCIPAL_H

#include "Ecran.h"

class MenuPrincipal : public Ecran
{
	public:
		MenuPrincipal(sf::RenderWindow &window);
		~MenuPrincipal() {};

		ecran_t executer(sf::Texture &derniereFenetre) override;
		std::unique_ptr<Ecran> factory() override;

	private:
		sf::Texture fondText_;
		sf::Sprite fond_;
		sf::Text version_;
		std::vector<sf::Text> textes_;

		int selection_ = -1;

};

#endif //MENU_PRINCIPAL_H
