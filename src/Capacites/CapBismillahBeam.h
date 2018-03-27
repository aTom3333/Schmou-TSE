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
		* Initialisation de la capacit�
		*/
		explicit CapBismillah(Ecran& ecran, const std::weak_ptr<Entite>& lanceur);
		/**
		* @fn utiliser
		* @brief Active la capacite
		* @param x Abscisse de la position o� la capacite est utilis�e
		* @param y Ordonn�e de la position o� la capacite est utilis�e
		*
		* Fonction Initialise la position de d�part et le timer
		*/
		void utiliser(proj_container& projectiles) override;
		/**
		* @fn actualiser
		* @brief Active les effets de la capacit�
		*
		* Cr�er 1 ProjPiou � l'activation
		* Actualise le timer
		* @param projectile Vecteur de tout les projectiles pr�sent � l'�cran
		* @param vaisseau Vaisseau qui a activ� la comp�tence
		*/
		void actualiser(proj_container& projectiles) override;

};

#endif // !CAPBISMILLAHBEAM_H
