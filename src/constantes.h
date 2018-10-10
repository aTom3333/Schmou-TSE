#ifndef CONSTANTES_H
#define CONSTANTES_H

#include <cstddef>

#define CHEMIN_RC "../../rc/"

#define PI acos(-1.0) /// Valeur de pi
#define VERSION "Debug."
#define BRANCHE "master"

constexpr float ECRAN_L = 1024; /// Largueur de la fenetre
constexpr float ECRAN_H = 768;  /// Hauteur de la fenetre

constexpr float OVERLAY_BARRE_L = 500; /// Largueur des barres de l'overlay
constexpr float OVERLAY_BARRE_H = 16;  /// Hauteur des barres de l'overlay

constexpr size_t NB_ACTION = 7; /// Nombre d'actions

constexpr size_t TEMPS_INVINCIBILITE = 2000; /// Nombres de millisecondes d'invincibilité par défaut

constexpr bool DEBUG = true;

enum Actions
{
    PAUSE, TIR1, TIR2, COMP1, COMP2, COMP3, ULTI
};

enum Equipe
{
    JOUEUR, ENNEMI, NEUTRE, ALLIE
};

enum ecran_t
{
    VIDE = -1, ACCUEIL = 0, MENU_PRINCIPAL, PARTIE, HANGAR
};

enum module_t
{
    ATTAQUE, DEFENSE, UTILITAIRE, DEPLACEMENT
};


#endif // CONSTANTES_H
