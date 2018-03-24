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

void chargement(sf::RenderWindow &window)
{
	sf::Clock timer;
	int alpha = 0;

	sf::Texture texture;
	sf::RectangleShape rect({ECRAN_L, ECRAN_H});
	sf::Sprite sprite;

	rect.setFillColor({ 0,0,0,0 });

	texture.loadFromFile("../../rc/Chargement/chargement.png");
	sprite.setTexture(texture);

	auto t = timer.restart();

	while (alpha < 15)
	{
		t = timer.getElapsedTime();
		if (t.asMilliseconds() > 50)
		{
			alpha += 3;

			if (alpha > 255)
				alpha = 255;

			rect.setFillColor({ 0, 0, 0, (sf::Uint8)alpha });
			t = timer.restart();
		}
		window.draw(rect);
		window.display();
	}

	window.draw(sprite);
	window.display();
}