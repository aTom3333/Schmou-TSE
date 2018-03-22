#include <SFML/Graphics.hpp>
#include <cmath>
#include <ctime>
#include <iostream>
#include "constantes.h"
#include "Entite.h"
#include "Utilitaires/Collision.h"
#include "Partie.h"
#include "Utilitaires/Divers.h"
#include "Projectiles/_projectiles.h"
#include <SFML/Audio.hpp>
//#include "Input.h"
#include "Utilitaires/Chargeur.h"


// Code minimal
int main()
{	
	//TG Pierre
	//sf::Music eyaeya;
	//eyaeya.openFromFile("../../rc/Musics/eyaeya.ogg");
	//eyaeya.setLoop(true);
	//eyaeya.play();
	
	sf::RenderWindow window(sf::VideoMode(ECRAN_L,ECRAN_H), "Schmou'TSE");
	Partie partie(window, Input::Media::Keyboard);

	srand(time(nullptr));

	partie.testPartie();
	

	return 0;
}

