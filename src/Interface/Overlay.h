#ifndef OVERLAY_H
#define OVERLAY_H

#include "SFML/Graphics.hpp"
#include "../Vaisseau/Vaisseau.h"
#include "../def_type.h"


/**
* @class Overlay
* @brief Classe qui gère l'overlay ingame
*
*/

class Overlay
{
	public:
		Overlay() = default;
		~Overlay();
		void init(vaisseau_ptr vaisseau);
		void draw(sf::RenderWindow &window, vaisseau_ptr vaisseau, bool bDraw = true) const;
		void gestion(vaisseau_ptr vaisseau);
		
	private :
		sf::Texture overlayText_; /// Texture de la partie de l'overlay qui n'intéragit pas
		sf::Sprite overlay_; /// Sprite de la partie de l'overlay qui n'intéragit pas

		sf::Font font_; /// Police des textes
		sf::Text *statuts_; /// Texte des cooldowns

		sf::RectangleShape barre_[3]; /// Rectangle indiquant la vie, l'armure et les boucliers
};


#endif // OVERLAY_H