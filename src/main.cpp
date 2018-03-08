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
//#include "Input.h"


// Code minimal
int main()
{

	//Brodel de thomas 2 : le retour
	ProjTest a;
//	std::cout << std::boolalpha << est<Projectile, decltype(a)>(a) << std::endl << est<ProjTest, decltype(a)>(a) << std::endl << est<ProjPiou, decltype(a)>(a) << std::endl;
	
	// Code propre

	sf::RenderWindow window(sf::VideoMode(ECRAN_L,ECRAN_H), "Schmou'TSE");
	Partie partie(window, Input::Media::Mouse, true, true);

	srand(time(nullptr));

	partie.testPartie();
	

	return 0;
}

