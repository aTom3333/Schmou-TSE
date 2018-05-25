#ifndef VAISSEAU_GARDIEN_H
#define VAISSEAU_GARDIEN_H

#include "../Vaisseau.h"

class VaisseauGardien : public Vaisseau
{
public:
	VaisseauGardien(Ecran& ecran);
	~VaisseauGardien() = default;
	void gestion(proj_container& proj_cont, Input& input) override;
	void destruction() override;
};

#endif // VAISSEAU_GARDIEN_H