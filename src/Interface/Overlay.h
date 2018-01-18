#ifndef OVERLAY_H
#define OVERLAY_H

#include "SFML/Graphics.hpp"
#include "../constantes.h"
#include "../Entite.h"

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
		void draw(sf::RenderWindow &window, bool bDraw = true);
		void gestion(Entite * vaisseau);
		
	private :
		sf::Texture overlayText_; /// Texture de la partie de l'overlay qui n'intéragie pas
		sf::Sprite overlay_; /// Sprite de la partie de l'overlay qui n'intéragie pas

		sf::Font font_; /// Police des textes
		sf::Text statuts_[4]; /// Texte d'info

		// TODO Solution temporaire
			sf::RectangleShape barre_[3]; /// Rectangle indiquant la vie, l'armure et les boucliers
};


#endif // OVERLAY_H