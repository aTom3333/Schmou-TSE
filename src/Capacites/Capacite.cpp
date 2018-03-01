#include <vector>
#include <string>
#include <algorithm>
#include "Capacite.h"
#include "../Vaisseau/Vaisseau.h"
#include "../Projectiles/Projectile.h"

void Capacite::initIcon(int i)
{
	capacite_.setPosition(900, 111 + i * 135);
	capacite_.setColor({ 255,255,255});
}
