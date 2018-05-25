#ifndef VAISSEAU_GRAVITY_H
#define VAISSEAU_GRAVITY_H

#include "../Vaisseau.h"

class VaisseauGravity : public Vaisseau
{
public:
    explicit VaisseauGravity(Ecran& ecran);
	~VaisseauGravity() = default;
	void gestion(proj_container& proj_cont, Input& input) override;
	void destruction() override;
};

#endif // VAISSEAU_GRAVITY_H