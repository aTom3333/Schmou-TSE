#include "Entite.h"
#include "Utilitaires/Collision.h"
#include "constantes.h"
#include <cmath>


bool collision(const Entite& e1, const Entite& e2)
{
	if (!e1.isInvincible() && !e2.isInvincible())
	{
		if (e1.actif_ && e2.actif_)
		{
			if (!e1.collisionnable_ && !e2.collisionnable_)
				return false;
			if (!e1.collisionneuse_ && !e2.collisionneuse_)
				return false;
			if ((e1.equipe_ == e2.equipe_ && e1.equipe_ != NEUTRE))
				return false;
			if (!collision(e1.cercleEnglobant_, e2.cercleEnglobant_))
				return false;
			for (const auto& f1 : e1.forme_)
				for (const auto& f2 : e2.forme_)
					if (collision(*f1, *f2))
						return true;
		}
	}
	
	return false;
}

void Entite::afficher(sf::RenderWindow & window, bool debug)
{
	if (equipe_ != JOUEUR)
	{
		if (framesInvincibilite_ == 0 || (framesInvincibilite_ / 10) % 2 == 0)
			sprite_.setColor({ 255, 255, 255 });
		else
			sprite_.setColor({ 255, 100, 100 });

		window.draw(sprite_);
	}
	else
	{
		if((framesInvincibilite_ / 10) % 2 == 0)
			window.draw(sprite_);
	}
	

	for (auto pos : positionsPrev_)
	{
		smoke_.setPosition(pos);
		window.draw(smoke_);
	}

	if(debug)
	{
		//window.draw(cercleEnglobant_);
		for (auto& elem : forme_)
			window.draw(*elem);
	}

	if(framesInvincibilite_ != 0) framesInvincibilite_--;
}


void Entite::move(sf::Vector2f delta)
{
	if(innate_)
	{
		sf::Vector2f taille = getTaille();
		sf::Vector2f pos = getPosition();
		if ((pos.x + taille.x + delta.x) > ECRAN_L) delta.x = ECRAN_L - pos.x - taille.x;
		if (pos.x + delta.x < 0) delta.x = -pos.x;
		if ((pos.y + taille.y + delta.y) > ECRAN_H) delta.y = ECRAN_H - pos.y - taille.y;
		if (pos.y + delta.y < 0) delta.y = -pos.y;
	}

		for (auto& elem : forme_)
			elem->move(delta);
		cercleEnglobant_.move(delta);
		sprite_.move(delta);

		if (nbPositions_)
		{
			positionsPrev_.push_front(position_);
			if (positionsPrev_.size() > nbPositions_)positionsPrev_.pop_back();
		}
		position_ += delta;
}

void Entite::setPosition(const sf::Vector2f & pos)
{
	move(pos - position_);
}


const sf::Vector2f& Entite::getPosition() const
{
	return position_;
}

void Entite::rotate(float angle)
{
	for(auto& elem : forme_)
		elem->rotate(angle);
    cercleEnglobant_.rotate(angle);
    sprite_.rotate(angle);
	angle_ = fmod(angle_ + angle, 360);
}

void Entite::setRotation(float angle)
{
	rotate(angle - angle_);
}

float Entite::getRotation() const
{
	return angle_;
}

void Entite::scale(float factor)
{
	for(auto& elem : forme_)
		elem->scale(factor, factor);
    cercleEnglobant_.scale(factor, factor);
    sprite_.scale(factor, factor);
	scale_ *= factor;
}

void Entite::setScale(float factor)
{
	scale(factor / scale_);
}

float Entite::getScale() const
{
	return scale_;
}

void Entite::changeSpeed(int val)
{
	vit_ += val;
}

void Entite::setDetruit(bool val)
{
	detruit_ = val;
}

bool Entite::estDetruit()
{
	if (pv_ <= 0 && isCollisionnable())
		detruit_ = true;
	return detruit_;
}

float Entite::getDegatsColl_() const
{
	return degatsColl_;
}

void Entite::setNbPositions(int val)
{
	nbPositions_ = val;
	if(val == 0) positionsPrev_.clear();
}

void Entite::setSmokeTexture(const sf::Texture &text, sf::Color couleur)
{
	textSmoke_ = text;
	smoke_.setTexture(textSmoke_);
	smoke_.setColor(couleur);
}

void Entite::regen(sf::Time t)
{
	// Mise à jour du timer
	t_regen_ += t.asMilliseconds();

	// Si 100 ms se sont écoulé
	if (t_regen_ >= 50)
	{
		// Réinitialisation du timer
		t_regen_ = 0;

		// Régénération des différentes statistiques
		pv_ += regenPV_;
		armure_ += regenARM_;
		bouclier_ += regenBOU_;

		// Si le seuil maximal est dépassé
		if (pv_ > pvM_)
			pv_ = pvM_;
		if (armure_ > armureM_)
			armure_ = armureM_;
		if (bouclier_ > bouclierM_)
			bouclier_ = bouclierM_;
	}
}

void Entite::recoitDegats(float degats)
{
	float restant = degats;

	if (degats != 0)
	{
		framesInvincibilite_ = NB_FRAMES_INVINCIBILITE;

		bouclier_ -= restant;

		// Si le bouclier est détruit
		if (bouclier_ < 0)
		{
			// Récupération des dégats restant
			restant = -bouclier_;
			bouclier_ = 0;
		}
		// Sinon le bouclier a absorbé tout les dégats 
		else
			restant = 0;

		float reductionArmure = 0.7; // Multiplicateur de réduction de dégats de l'armure
		armure_ -= restant * reductionArmure;
		if (armure_ < 0)
		{
			restant = -armure_ / reductionArmure;
			armure_ = 0;
		}
		else
			restant = 0;

		pv_ -= restant;
		if (pv_ <= 0)
		{
			pv_ = 0;
			detruit_ = true;
			destruction();
		}
	}
}

bool Entite::estDehors(float x_min, float y_min, float x_max, float y_max) const
{
    float R = cercleEnglobant_.getRadius();
    return position_.x < x_min - R || position_.x > x_max + R || position_.y < y_min - R || position_.y > y_max + R;
}

bool Entite::estDedans(float x_min, float y_min, float x_max, float y_max) const
{
    float R = cercleEnglobant_.getRadius();
    return position_.x > x_min + R && position_.x < x_max - R && position_.y > y_min + R && position_.y < y_max - R;
}
