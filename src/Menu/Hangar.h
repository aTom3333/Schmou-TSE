#ifndef HANGAR_H
#define HANGAR_H

#include "../constantes.h"
#include "Ecran.h"
#include "../Vaisseau/Vaisseau.h"


#define NB_STATS 5
#define BARRE_STATS_W 240
#define BARRE_STATS_H 10


// TODO CL Constantes à ajuster
constexpr float MAX_PV = 5000.f, MAX_ARMURE = 1000.f, MAX_BOUCLIER = 5000.f;
constexpr float MAX_ATK = 2000.f, MAX_VITESSE = 1500.f;

constexpr float milieuX = 465, milieuY = 230;
constexpr float droiteX = 570, gaucheX = 360;

constexpr float TEMPS_ANIMATION = 0.5f;

class Hangar : public Ecran
{
	public:
		Hangar(sf::RenderWindow &window);
		~Hangar() {};

		ecran_t executer(std::vector<std::unique_ptr<Ecran>>& vectEtats, sf::Texture &derniereFenetre) override;
		std::unique_ptr<Ecran> factory() override;
	private:
		sf::Sprite fond_, selection_;
		sf::RectangleShape description_;
		sf::Text nom_, titreDescription_;
		sf::Text stats_[NB_STATS];
		sf::RectangleShape barres_[NB_STATS];
		float positionModeleX_, positionModeleY_;
		float destinationX_, departX_;
		sf::Vector2f posSelection_ = { 0, 0 };
		bool animation_ = false;

		void drawStats();
		void drawOverview();
		void move();
};

#endif // !HANGAR_H
