#ifndef VAISSEAUTEST_H
#define VAISSEAUTEST_H

#include "Vaisseau.h"
#include "../Capacites/Capacite.h"
#include "../Capacites/_Capacites.h"

class VaisseauTest : public Vaisseau
{
public:
	VaisseauTest(Ecran& ecran);
	~VaisseauTest() = default;
	void gestion(proj_container proj_cont, Input& input) override;
	/**
	* @fn destruction
	* @brief règle l'attribut detruit_ à true
	*
	* Procédure à effectuer lorsque le vaisseau est détruit
	*/
	void destruction() override { detruit_ = true; }
};





#endif // VAISSEAUTEST_H


