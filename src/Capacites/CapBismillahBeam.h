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
		* @param projectiles Vecteur de tout les projectiles présents à l'écran
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
		* @param projectiles Vecteur de tout les projectiles présents à l'écran
		*/
		void actualiser(proj_container& projectiles) override;

};

#endif // !CAPBISMILLAHBEAM_H
