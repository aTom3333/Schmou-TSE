#include <SFML/Graphics.hpp>
#include "Partie.h"


// Code minimal
int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Schmou'TSE");
	Partie partie;

	partie.jeu(&window);
	

	return 0;
}

