#ifndef CONSTANTES_H
#define CONSTANTES_H

#define PI acos(-1) /// Valeur de pi

#define ECRAN_L 1024 /// Largueur de la fenetre
#define ECRAN_H 768 /// Hauteur de la fenetre

#define OVERLAY_BARRE_L 500 /// Largueur des barres de l'overlay
#define OVERLAY_BARRE_H 16 /// Hauteur des barres de l'overlay

#define NB_ACTION 7 /// Nombre d'actions

#define NB_FRAMES_INVINCIBILITE 60 /// Nombres de frames d'invincibilités


enum Actions
{
    PAUSE , TIR1, TIR2, COMP1, COMP2, COMP3, ULTI
};

enum Equipe
{
	JOUEUR, ENNEMI, NEUTRE ,ALLIE
};


#endif // CONSTANTES_H