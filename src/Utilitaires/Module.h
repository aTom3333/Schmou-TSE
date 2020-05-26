#ifndef MODULE_H
#define MODULE_H

#include "../constantes.h"
#include "../Menu/Ecran.h"

#include <SFML/Graphics.hpp>
#include <string>


class Module
{
    public:
    explicit Module(Ecran& ecran, module_t type = UTILITAIRE, float x = 0, float y = 0);
    ~Module() {};
    void init(size_t id);
    void checkSelection(sf::Vector2f curseur, sf::Vector2f& res, float offsetX, float offsetY);
    int checkPosition(float size);

    void setPositionModules(float x, float y);
    sf::Sprite getSprite() const { return sprite_; }

    std::wstring getNom() const { return nom_; }


    private :
    // Stat généraux
    Ecran& ecran_;
    module_t type_;
    float x_, y_;
    sf::Sprite sprite_;

    // Particularité du module
    std::wstring nom_;
    size_t id_ = 0;
    float pvM_ = 0.f, pvRegen_ = 0.f;
    float armureM_ = 0.f, armureRegen_ = 0.f;
    float bouclierM_ = 0.f, bouclierRegen_ = 0.f;
    float atk_ = 0.f, vit_ = 0.f;
};


#endif // !MODULE_H

