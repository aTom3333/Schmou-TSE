#include "Trajectoire.h"
#include "../constantes.h"

sf::Vector2f traj_position(Trajectoire trajectoire,float t, float vit_, sf::Vector2f posInit, std::vector<float> params)
{
	sf::Vector2f posOut;//position de sortie
	switch (trajectoire)
	{
		// Si la trajectoire est linéaire
	case LINEAIRE:
		posOut.x = posInit.x + params[0]*vit_*t / 100;
		posOut.y = params[1] * (posOut.x - posInit.x) + posInit.y;
		break;
		// Si la trajectoire est parabolique
	case PARABOLIQUE:
		posOut.x = posInit.x + params[0]*vit_*t / 100;
		posOut.y = (posInit.y - params[1]) / ((posInit.x - params[2])*(posInit.x - params[2])) * (posOut.x - params[2]) * (posOut.x - params[2]) + params[1];
		break;
		// Si la trajectoire est sinusoidale
	case SINUS:
		posOut.x = posInit.x + params[0]*vit_*t / 130;
		posOut.y = params[3] * (posOut.x - posInit.x) + posInit.y + params[2] * sin(2 * PI / params[1] * posOut.x);
		break;
	default:
		break;
	}
	return posOut;

}
