#include <vector>
#include <string>
#include <algorithm>
#include "Capacite.h"
#include "Vaisseau.h"
#include "Projectile.h"


Vaisseau::Vaisseau(bool player)
{
	//presonnalisation
	player_ = player;
	//stats de base
	pvM_ = 100;
	atqM_ = 100;
	defM_ = 100;
	vitM_ = 100;

}

Vaisseau::~Vaisseau()
{
}
