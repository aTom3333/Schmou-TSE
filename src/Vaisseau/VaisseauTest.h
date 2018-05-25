#ifndef VAISSEAUTEST_H
#define VAISSEAUTEST_H

#include "Vaisseau.h"

class VaisseauTest : public Vaisseau
{
public:
    explicit VaisseauTest(Ecran& ecran);
	~VaisseauTest() = default;
	void gestion(proj_container& proj_cont, Input& input) override;
	/**
	* @fn destruction
	* @brief règle l'attribut detruit_ à true
	*
	* Procédure à effectuer lorsque le vaisseau est détruit
	*/
	void destruction() override ;
};





#endif // VAISSEAUTEST_H


