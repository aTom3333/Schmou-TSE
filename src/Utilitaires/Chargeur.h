#ifndef SCHMOUTSE_CHARGEUR_H
#define SCHMOUTSE_CHARGEUR_H

#include "optional.h"
#include <memory>
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <SFML/Audio.hpp>


class Chargeur
{
    public:
        Chargeur();
        std::shared_ptr<sf::Texture> getTexture(const std::string& name);
        std::shared_ptr<sf::SoundBuffer> getSoundBuffer(const std::string& name);
    
    private:
        static std::map<std::string, std::string> location_;
        static bool loaded_;
        std::map<std::string, std::shared_ptr<sf::Texture>> textures_;
        std::map<std::string, std::shared_ptr<sf::SoundBuffer>> sound_buffers_;
};


#endif //SCHMOUTSE_CHARGEUR_H
