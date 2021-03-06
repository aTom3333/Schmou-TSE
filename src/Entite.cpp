#include "Entite.h"
#include "Utilitaires/Collision.h"
#include "constantes.h"
#include <cmath>

bool collision(const Entite& e1, const Entite& e2)
{
    if(!e1.isInvincible() && !e2.isInvincible())
    {
        if(e1.actif_ && e2.actif_)
        {
            if(!e1.collisionnable_ && !e2.collisionnable_) //si aucun n'est collisionnable
                return false;
            if(!e1.collisionneuse_ && !e2.collisionneuse_) //si aucun n'est collisionneur
                return false;
            if((e1.equipe_ == e2.equipe_ && e1.equipe_ != NEUTRE)) //si même équipe, qui n'est pas NEUTRE
                return false;
            if(!collision(e1.cercleEnglobant_, e2.cercleEnglobant_)) //premier test rapide des Cercles Englobants
                return false;
            for(const auto& f1 : e1.forme_) //deuxième test précis des formes
                for(const auto& f2 : e2.forme_)
                    if(collision(*f1, *f2))
                        return true;
        }
    }

    return false;
}

void Entite::afficher(const bool debug)
{
    auto& window = ecran_.getWindow();


    if(invincible_) //clignotement en cas d'invulnérabilité
    {
        const unsigned short nbClignotement = 10;
        //nb de clignotements(passage de normal à rouge puis rouge à normal) pendant le temps d'invicibilité imparti t_Invincibilite

        int quotient;
        std::remquo(static_cast<float>(t_invincible_courant.asMilliseconds()),
                    t_Invincibilite_.asMilliseconds() / (2 * nbClignotement), &quotient);

        //std::cerr << t_invincible_courant.asMilliseconds() <<" div : "<< t_Invincibilite_.asMilliseconds() / (2 * nbClignotement)<< "  quot : "<<quotient<<std::endl;

        if(quotient % 2 == 0)
        {
            for(auto& sprite : sprites_)
                window.draw(sprite);
        }
        else
        {
            for(auto& sprite : sprites_)
            {
                sf::Sprite temp_sprite = sprite;
                temp_sprite.setColor({255, 100, 100, 128});
                window.draw(temp_sprite);
            }
        }

        t_invincible_courant += ecran_.getTempsFrame();
        if(t_invincible_courant >= t_Invincibilite_)
            invincible_ = false;
    }
    else //affichage normal
    {
        for(auto& sprite : sprites_)
            window.draw(sprite);
    }

    for(auto& pos : positionsPrev_)
    {
        smoke_.setPosition(pos);
        window.draw(smoke_);
    }

    afficher_debug(debug);
}

void Entite::afficher_debug(bool debug)
{
    if(DEBUG ^ debug)
    {
        //cercle englobant en rouge mi-transparent
        cercleEnglobant_.setFillColor({255, 100, 100, 128});
        ecran_.getWindow().draw(cercleEnglobant_);
        //hitbox en jaune mi-transparent
        for(auto& elem : forme_)
        {
            elem->setFillColor({255, 255, 100, 128});
            ecran_.getWindow().draw(*elem);
        }
    }
}


void Entite::move(sf::Vector2f delta)
{
    if(innate_)
    {
        const sf::Vector2f taille = getTailleSprite();
        sf::Vector2f pos = getPosition() - getOrigin();
        if((pos.x + taille.x + delta.x) > ECRAN_L)
            delta.x = ECRAN_L - pos.x - taille.x;
        else
            if(pos.x + delta.x < 0)
                delta.x = -pos.x;
        if((pos.y + taille.y + delta.y) > ECRAN_H)
            delta.y = ECRAN_H - pos.y - taille.y;
        else
            if(pos.y + delta.y < 0)
                delta.y = -pos.y;
    }

    for(auto& elem : forme_)
        elem->move(delta);
    for(auto& sprite : sprites_)
        sprite.move(delta);
    cercleEnglobant_.move(delta);

    //TODO PG il faut gérer ça avec les origines
    if(nbPositions_)
    {
        positionsPrev_.push_front(position_);
        if(positionsPrev_.size() > nbPositions_)
            positionsPrev_.pop_back();
    }
    position_ += delta;
}

void Entite::move()
{
    move({
        static_cast<float>(-vit_ * cos(fmod((PI / 180 * rotation_), 90)) * ecran_.getTempsFrame().asSeconds()),
        static_cast<float>(-vit_ * sin(fmod((PI / 180 * rotation_), 90)) * ecran_.getTempsFrame().asSeconds())
    });
}

void Entite::setPosition(const sf::Vector2f& pos)
{
    move(pos - position_);
}


void Entite::rotate(float angle)
{
    for(auto& elem : forme_)
        elem->rotate(angle);

    cercleEnglobant_.rotate(angle);

    for(auto& sprite : sprites_)
        sprite.rotate(angle);

    rotation_ = fmod(rotation_ + angle, 360);
}

void Entite::setRotation(float angle)
{
    rotate(angle - rotation_);
}


void Entite::scale(float factor)
{
    for(auto& elem : forme_)
        elem->scale(factor, factor);
    cercleEnglobant_.scale(factor, factor);
    for(auto& elem : sprites_)
        elem.scale(factor, factor);
    scale_ *= factor;
}

void Entite::setScale(float factor)
{
    scale(factor / scale_);
}

void Entite::setDetruit(bool val)
{
    detruit_ = val;
}

bool Entite::estDetruit()
{
    if(pv_ <= 0)
        detruit_ = true;
    return detruit_;
}

float Entite::getDegatsColl_() const
{
    return degatsCollision_;
}

void Entite::setNbPositions(size_t val)
{
    nbPositions_ = val;
    if(val == 0)
        positionsPrev_.clear();
}

void Entite::setSmokeTexture(const sf::Texture& text, sf::Color couleur)
{
    smoke_.setTexture(text);
    smoke_.setColor(couleur);
    smoke_.setOrigin(origine_);
}

void Entite::setOrigin(sf::Vector2f origine)
{
    const auto delta = origine - origine_;
    origine_ = origine;

    //vecteur de sprites_
    for(auto& sprite : sprites_)
    {
        sprite.setOrigin(delta + sprite.getOrigin());
    }

    //cercle englobant
    cercleEnglobant_.setOrigin(delta + cercleEnglobant_.getOrigin());

    //forme / hitbox
    for(auto& forme : forme_)
    {
        forme->setOrigin(delta + forme->getOrigin());
    }
}

void Entite::regen()
{
    // Régénération des différentes statistiques
    pv_ += regenPv_ * ecran_.getTempsFrame().asSeconds();
    armure_ += regenArmure_ * ecran_.getTempsFrame().asSeconds();
    bouclier_ += regenBouclier_ * ecran_.getTempsFrame().asSeconds();

    // Si le seuil maximal est dépassé
    if(pv_ > pvM_)
        pv_ = pvM_;
    if(armure_ > armureM_)
        armure_ = armureM_;
    if(bouclier_ > bouclierM_)
        bouclier_ = bouclierM_;
}

void Entite::recoitDegats(float degats)
{
    float restant = degats;

    if(degats != 0)
    {
        //TODO PG pas génial, non ?
        //feedback visuel pour les ennemis touchés
        if(equipe_ == ENNEMI)
            for(auto& sprite : sprites_)
            {
                sf::Sprite temp_sprite = sprite;
                temp_sprite.setColor({0, 0, 0, 255});
                ecran_.getWindow().draw(temp_sprite);
            }

        //BOUCLIER
        bouclier_ -= restant;

        // Si le bouclier est détruit
        if(bouclier_ < 0)
        {
            // Récupération des dégats restant
            restant = -bouclier_;
            bouclier_ = 0;
        }
            // Sinon le bouclier a absorbé tout les dégats 
        else
        {
            //restant = 0;
            return;
        }

        //frames d'invulnérabilité si des dégats traversent le bouclier
        if(invincibilable_)
        {
            invincible_ = true;
            t_invincible_courant = sf::Time::Zero;
        }


        //ARMURE
        static const float REDUCTION_ARMURE = 0.7f; // Multiplicateur de réduction de dégats de l'armure
        armure_ -= restant * REDUCTION_ARMURE;
        if(armure_ < 0)
        {
            restant = -armure_ / REDUCTION_ARMURE;
            armure_ = 0;
        }
        else
        {
            //restant = 0;
            return;
        }

        //PV
        pv_ -= restant;
        if(pv_ <= 0)
        {
            pv_ = 0;
            detruit_ = true;
            destruction();
        }
    }
}

bool Entite::estDehors(float x_min, float y_min, float x_max, float y_max) const
{
    const float R = cercleEnglobant_.getRadius();
    return position_.x < x_min - R || position_.x > x_max + R || position_.y < y_min - R || position_.y > y_max + R;
}

bool Entite::estDedans(float x_min, float y_min, float x_max, float y_max) const
{
    const float R = cercleEnglobant_.getRadius();
    return position_.x > x_min + R && position_.x < x_max - R && position_.y > y_min + R && position_.y < y_max - R;
}
