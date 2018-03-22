#ifndef CONSTANTES_H
#define CONSTANTES_H

#define PI acos(-1.0) /// Valeur de pi

constexpr float ECRAN_L = 1024; /// Largueur de la fenetre
constexpr float ECRAN_H = 768; /// Hauteur de la fenetre

constexpr float OVERLAY_BARRE_L = 500; /// Largueur des barres de l'overlay
constexpr float OVERLAY_BARRE_H = 16; /// Hauteur des barres de l'overlay

constexpr size_t NB_ACTION = 7; /// Nombre d'actions

constexpr size_t NB_FRAMES_INVINCIBILITE = 60; /// Nombres de frames d'invincibilités


enum Actions
{
    PAUSE , TIR1, TIR2, COMP1, COMP2, COMP3, ULTI
};

enum Equipe
{
	JOUEUR, ENNEMI, NEUTRE ,ALLIE
};


#endif // CONSTANTES_H