#ifndef CAPBISMILLAHBEAM_H
#define CAPBISMILLAHBEAM_H

#include "Capacite.h"

class CapBismillah : public Capacite
{
	public:
		/**
		* @fn CapPiou::CapPiou
		* @brief Constructeur
		*
		* Initialisation de la capacité
		*/
		explicit CapBismillah(Ecran& ecran, const std::weak_ptr<Entite>& lanceur);
		/**
		* @fn utiliser
		* @brief Active la capacite
		* @param x Abscisse de la position où la capacite est utilisée
		* @param y Ordonnée de la position où la capacite est utilisée
		*
		* Fonction Initialise la position de départ et le timer
		*/
		void utiliser(proj_container& projectiles) override;
		/**
		* @fn actualiser
		* @brief Active les effets de la capacité
		*
		* Créer 1 ProjPiou à l'activation
		* Actualise le timer
		* @param projectile Vecteur de tout les projectiles présent à l'écran
		* @param vaisseau Vaisseau qui a activé la compétence
		*/
		void actualiser(proj_container& projectiles) override;

};

#endif // !CAPBISMILLAHBEAM_H
