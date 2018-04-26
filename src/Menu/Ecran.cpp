#include "Ecran.h"
#include "../Utilitaires/Divers.h"


Ecran::Ecran(sf::RenderWindow& window) :  window_{ window }
{
	//polices
	sf::Font temp_font;
	temp_font.loadFromFile("../../rc/Font/hemi.ttf");

	polices_["hemi"] = temp_font;
	temp_font.loadFromFile("../../rc/Font/whitrabt.ttf");
	polices_["whitrabt"] = temp_font;

}

std::optional<ecran_t> Ecran::gestionEvent(const sf::Event& event)
{
    if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Delete))
    	return std::make_optional(VIDE);
    else if(event.type == sf::Event::Resized) {
		adapt_viewport(window_);
		return std::nullopt;
	}
	
	return std::nullopt;
}

void chargement(sf::RenderWindow &window, sf::Texture& derniereFenetre)
{
	sf::Clock timer;
	size_t alpha = 50;

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

void fade(sf::RenderWindow & window, sf::Texture & derniereFenetre)
{
	sf::Clock timer;
	size_t alpha = 50;

	sf::RectangleShape rect({ ECRAN_L, ECRAN_H });
	sf::Sprite sprite, fond;

	rect.setFillColor({ 0,0,0,0 });

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
}

