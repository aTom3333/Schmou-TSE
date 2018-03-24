#ifndef SCHMOUTSE_CHARGEUR_H
#define SCHMOUTSE_CHARGEUR_H

#include "optional.h"
#include <memory>
#include <SFML/Graphics.hpp>
#include <map>
#include <string>


class Chargeur
{
    public:
        Chargeur();
        const sf::Texture& getTexture(const std::string& name);
    
    private:
        static std::map<std::string, std::string> location_;
        static bool loaded_;
        std::map<std::string, sf::Texture> textures_;
};


#endif //SCHMOUTSE_CHARGEUR_H
