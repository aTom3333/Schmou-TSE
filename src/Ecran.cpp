#include "Ecran.h"

Ecran::Ecran(std::stack<std::unique_ptr<Ecran>>& pile) : pile_{ pile }
{
	//polices
	sf::Font temp_font;
	temp_font.loadFromFile("../../rc/Font/hemi.ttf");
	polices_.push_back(temp_font);
	temp_font.loadFromFile("../../rc/Font/whitrabt.ttf");
	polices_.push_back(temp_font);
}
//é à ù 