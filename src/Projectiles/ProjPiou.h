#ifndef PROJ_PIOU_H
#define PROJ_PIOU_H

#include "Projectile.h"


class ProjPiou : public Projectile
{
public:
	ProjPiou();
	ProjPiou(int x, int y);
	~ProjPiou();
	void gestion(sf::RenderWindow &window);
private:
	int mx_;
	int my_;
	int vx_, vy_;
};

#endif
