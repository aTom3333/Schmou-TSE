#include "ProjMissile.h"
#include <cmath>


ProjMissile::ProjMissile()
{

}

ProjMissile::ProjMissile(float x, float y, Equipe equipe)
{
    // Gestion du sprite
    texture_.loadFromFile("../../rc/Sprites/base/projectile_missile.png");
    sprite_.setTexture(texture_);

    // Hitbox
    cercleEnglobant_ = sf::CircleShape(sqrt(20*20+40*40));
    cercleEnglobant_.setOrigin(sqrt(20 * 20 + 40 * 40), sqrt(20 * 20 + 40 * 40));
    cercleEnglobant_.setPosition(20, 40);
    forme_.emplace_back(new sf::RectangleShape({40,80}));

    //stats
    equipe_ = equipe;
    pvM_ = 10;
    armureM_ = 0;
    bouclierM_ = 0;

    pv_ = pvM_;
    armure_ = armureM_;
    bouclier_ = bouclierM_;
    actif_ = true;

    regenARM_ = regenBOU_ = regenPV_ = 0;

    degatsColl_ = 300;

    //  Projectile qui se déplace verticalement
    sens_ = 1;
    a_ = 1.07 * sens_;
    v_ = 10 * sens_;
    setPosition({ x, y });
}

ProjMissile::~ProjMissile()
{
}

void ProjMissile::gestion(sf::RenderWindow & window, sf::Time tempsEcoule)
{
    v_ *= a_;
    if (v_*tempsEcoule.asSeconds() > 30)
        v_ = 30/ tempsEcoule.asSeconds();
    setPosition({ position_.x, position_.y + v_*tempsEcoule.asSeconds() });
    afficher(window);
}

void ProjMissile::agit(Entite & e)
{
    e.recoitDegats(degatsColl_);
    detruit_ = true;
}
