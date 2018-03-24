#include "Ecran.h"

Ecran::Ecran(sf::RenderWindow& window) :  window_{ window }
{
	//polices
	sf::Font temp_font;
	temp_font.loadFromFile("../../rc/Font/hemi.ttf");

	polices_["hemi"] = temp_font;
	temp_font.loadFromFile("../../rc/Font/whitrabt.ttf");
	polices_["whitrabt"] = temp_font;

}

void chargement(sf::RenderWindow &window, sf::Texture& derniereFenetre)
{
	sf::Clock timer;
	int alpha = 50;

	sf::Texture texture;
	sf::RectangleShape rect({ECRAN_L, ECRAN_H});
	sf::Sprite sprite, fond;

	rect.setFillColor({ 0,0,0,0 });

	texture.loadFromFile("../../rc/Chargement/chargement.png");
	sprite.setTexture(texture);
	fond.setTexture(derniereFenetre);

	auto t = timer.restart();

	while (alpha < 255)
	{
		t = timer.getElapsedTime();
		if (t.asMilliseconds() > 50)
		{
			alpha += 50;

			if (alpha > 255)
				alpha = 255;

			rect.setFillColor({ 0, 0, 0, (sf::Uint8)alpha });
			t = timer.restart();
		}
		window.clear();
		window.draw(fond);
		window.draw(rect);
		window.display();
	}

	window.clear();
	window.draw(sprite);
	window.display();
}