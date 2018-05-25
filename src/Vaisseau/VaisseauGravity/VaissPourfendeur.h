#ifndef VAISSEAU_POURFENDEUR_H
#define VAISSEAU_POURFENDEUR_H

#include "../Vaisseau.h"

class VaisseauPourfendeur : public Vaisseau
{
public:
	VaisseauPourfendeur(Ecran& ecran);
	~VaisseauPourfendeur() = default;
	void gestion(proj_container& proj_cont, Input& input) override;
	void destruction() override;
};

#endif // VAISSEAU_POURFENDEUR_H