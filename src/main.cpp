#include "constantes.h"
#include "Entite.h"
#include "Utilitaires/Collision.h"
#include "Partie.h"
#include "Utilitaires/Divers.h"
#include "Projectiles/_projectiles.h"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <ctime>
#include <iostream>
#include <SFML/Audio.hpp>
#include <string>
//#include "Input.h"
#include "Utilitaires/Chargeur.h"


// Code minimal
int main(int argc, char* argv[])
{	
	//if (argv[0] != std::string("Schmou'TSE")) //TODO PG faire de la merde avec istringstream

	//TG Pierre
	//sf::Music eyaeya;
	//eyaeya.openFromFile("../../rc/Musics/eyaeya.ogg");
	//eyaeya.setLoop(true);
	//eyaeya.play();
	
	//TODO PG refaire l'aléatoire
	srand(time(nullptr));

	//Fenêtre
	sf::RenderWindow window(sf::VideoMode(ECRAN_L,ECRAN_H), "Schmou'TSE");

	//Stack d'écran
	std::stack<std::unique_ptr<Ecran>> pile;

	//Lancement de partie	
	pile.emplace(new Partie(pile, window, Input::Media::Keyboard));

	bool continuer = true;

	pile.top()->executer(); 
	
	

	return 0;
}

