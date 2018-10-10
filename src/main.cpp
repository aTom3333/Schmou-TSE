#include "constantes.h"
#include "Entite.h"
#include "Menu/Partie.h"
#include "Menu/Accueil.h"
#include "Menu/MenuPrincipal.h"
#include "Menu/Hangar.h"
#include "Utilitaires/Chargeur.h"
#include "Utilitaires/utilities.h"

#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>


// Code minimal
int main(int argc, char* argv[])
{	
	//if (argv[0] != std::string("Schmou'TSE")) //TODO PG faire de la merde avec istringstream

	//TODO CL tueur de son
	sf::Listener::setGlobalVolume(100);

	//TG Pierre
    //sf::Music eyaeya;
    //eyaeya.openFromFile("../../rc/Musics/Divers/eyaeya.ogg");
    //eyaeya.setLoop(true);
    //eyaeya.play();

    //sf::Music intro;
    //intro.openFromFile("../../rc/Musics/Divers/intro_wtf.wav");
    //intro.setLoop(false);
    //intro.play();

	//Fenêtre
	sf::RenderWindow window(sf::VideoMode(ECRAN_L,ECRAN_H), "Schmou'TSE");
    const sf::View view1(sf::FloatRect(0, 0, ECRAN_L, ECRAN_H));
    window.setView(view1);

	//Stack d'écran
	std::vector<std::unique_ptr<Ecran>> vectEtats;

    sf::Texture temp_texture;
	chargement(window, temp_texture);

	//Lancement de partie	
	vectEtats.emplace_back(new Accueil(window));
	vectEtats.emplace_back(new MenuPrincipal(window));
	vectEtats.emplace_back(new Partie(window, Input::Media::Mouse));
	vectEtats.emplace_back(new Hangar(window));

	ecran_t etat = PARTIE;//TODO PG écran de départ actuel

	while (etat != VIDE)
	{
		sf::Texture derniereFenetre;
		derniereFenetre.create(ECRAN_L, ECRAN_H);
		etat = vectEtats.at(etat)->executer(vectEtats, derniereFenetre);

		for (auto& ecran : vectEtats)
		{
			if (ecran->isDetruit())
			{
				chargement(window, derniereFenetre);
				auto ecran_temp = ecran->factory();
				ecran.reset();
				ecran = std::move(ecran_temp);
			}
		}
	}

	return 0;
}

