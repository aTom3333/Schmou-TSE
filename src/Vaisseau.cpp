#include <vector>
#include <string>
#include <algorithm>
#include "Capacite.h"
#include "Vaisseau.h"
#include "Projectile.h"


Vaisseau::Vaisseau(bool player)
{
	//presonnalisation
	_player = player;
	//stats de base
	_pvM = 100;
	_atqM = 100;
	_defM = 100;
	_vitM = 100;

}

Vaisseau::~Vaisseau()
{
}
