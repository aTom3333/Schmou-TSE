#include "constantes.h"
#include "Entite.h"
#include "Utilitaires/Collision.h"
#include "Menu/Partie.h"
#include "Menu/Accueil.h"
#include "Utilitaires/Divers.h"
#include "Projectiles/_projectiles.h"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <ctime>
#include <iostream>
#include <SFML/Audio.hpp>
#include <string>
#include "Utilitaires/Chargeur.h"


// Code minimal
int main(int argc, char* argv[])
{	
	//if (argv[0] != std::string("Schmou'TSE")) //TODO PG faire de la merde avec istringstream

	//TG Pierre
    //sf::Music eyaeya;
    //eyaeya.openFromFile("../../rc/Musics/Divers/eyaeya.ogg");
    //eyaeya.setLoop(true);
    //eyaeya.play();

    /*sf::Music intro;
    intro.openFromFile("../../rc/Musics/Divers/intro_wtf.wav");
    intro.setLoop(false);
    intro.play();*/
	
	//TODO PG refaire l'aléatoire
	srand(time(nullptr));

	//Fenêtre
	sf::RenderWindow window(sf::VideoMode(ECRAN_L,ECRAN_H), "Schmou'TSE");

	//Stack d'écran
	std::vector<std::unique_ptr<Ecran>> vectEtats;

	//Lancement de partie	
	vectEtats.emplace_back(new Accueil(window));
	vectEtats.emplace_back(new Partie(window, Input::Media::Keyboard));

	ecran_t etat = PARTIE; //TODO modifier ici pour lancer menu directemnt, ACCUEIL normalement

	while (etat != VIDE)
	{
		etat = vectEtats.at(etat)->executer();
		for (auto& ecran : vectEtats)
		{
			if (ecran->isDetruit())
			{
				auto ecran_temp = ecran->factory();
				ecran.reset();
				ecran = std::move(ecran_temp);
			}
		}
	}

	return 0;
}

