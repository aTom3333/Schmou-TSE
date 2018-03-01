#ifndef OVERLAY_H
#define OVERLAY_H

#include "SFML/Graphics.hpp"
#include "../constantes.h"
#include "../Vaisseau/Vaisseau.h"


/**
* @class Overlay
* @brief Classe qui gère l'overlay ingame
*
*/

class Overlay
{
	public:
		Overlay();
		~Overlay();
		void init(Vaisseau *vaisseau);
		void draw(sf::RenderWindow &window, Vaisseau *vaisseau, bool bDraw = true);
		void gestion(Vaisseau * vaisseau);
		
	private :
		sf::Texture overlayText_; /// Texture de la partie de l'overlay qui n'intéragie pas
		sf::Sprite overlay_; /// Sprite de la partie de l'overlay qui n'intéragie pas

		sf::Font font_; /// Police des textes
		sf::Text *statuts_; /// Texte d'info

		// TODO Solution temporaire
			sf::RectangleShape barre_[3]; /// Rectangle indiquant la vie, l'armure et les boucliers
};


#endif // OVERLAY_H