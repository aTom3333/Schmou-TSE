#ifndef CONSTANTES_H
#define CONSTANTES_H

#define PI 3.14159265359 /// Valeur de pi

#define ECRAN_L 1024 /// Largueur de la fenetre
#define ECRAN_H 768 /// Hauteur de la fenetre

#define NB_ACTION 2 /// Nombre d'actions

enum Trajectoire
{
	LINEAIRE,
	PARABOLIQUE,
	SINUS
};

enum Actions
{
    Pause, Tir1, Tir2, Comp1, Comp2, Comp3, Comp4
};


#endif // CONSTANTES_H