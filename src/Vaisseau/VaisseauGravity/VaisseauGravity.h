#ifndef VAISSEAU_GRAVITY_H
#define VAISSEAU_GRAVITY_H

#include "../Vaisseau.h"
#include "../../Capacites/Capacite.h"
#include "../../Capacites/_Capacites.h"

class VaisseauGravity : public Vaisseau
{
public:
	VaisseauGravity(Ecran& ecran);
	~VaisseauGravity() = default;
	void gestion(proj_container& proj_cont, Input& input) override;
	void destruction() override;
};

#endif // VAISSEAU_GRAVITY_H