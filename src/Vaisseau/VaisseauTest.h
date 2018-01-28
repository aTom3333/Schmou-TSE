#ifndef VAISSEAUTEST_H
#define VAISSEAUTEST_H

#include "Vaisseau.h"
#include "../Capacites/Capacite.h"
#include "../Capacites/_Capacites.h"

class VaisseauTest : public Vaisseau
{
public:
	VaisseauTest();
	~VaisseauTest();
	void gestion(sf::RenderWindow & window, sf::Time tempsEcoule, Input input);
	/**
	* @fn destruction
	* @brief Procedure a effectuer lorsque le vaisseau est d�truit
	*
	* D�truit l'entit�
	*/
	void destruction() { detruit_ = true; }

private:
	int attaqueEnCours_;
};





#endif // VAISSEAUTEST_H


