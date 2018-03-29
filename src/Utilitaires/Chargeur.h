#ifndef SCHMOUTSE_CHARGEUR_H
#define SCHMOUTSE_CHARGEUR_H

#include "optional.h"
#include <memory>
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <SFML/Audio.hpp>

struct caseInsensitiveCompare
{
	bool operator()(const std::string& a, const std::string& b);
};

class Chargeur
{
    public:
        Chargeur();
        std::shared_ptr<sf::Texture> getTexture(const std::string& name, const bool& repeated = false, const bool& smooth = true, const sf::IntRect& area = sf::IntRect());
        std::shared_ptr<sf::SoundBuffer> getSoundBuffer(const std::string& name);
		std::shared_ptr<sf::Font> getFont(const std::string& name);
    
    private:
        static std::map<std::string, std::string, caseInsensitiveCompare> location_;
        static bool loaded_;
        std::map<std::string, std::shared_ptr<sf::Texture>, caseInsensitiveCompare> textures_;
        std::map<std::string, std::shared_ptr<sf::SoundBuffer>, caseInsensitiveCompare> sound_buffers_;
		std::map<std::string, std::shared_ptr<sf::Font>, caseInsensitiveCompare> fonts_;
};


#endif //SCHMOUTSE_CHARGEUR_H
