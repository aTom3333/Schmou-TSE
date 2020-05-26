#include "Chargeur.h"
#include "../constantes.h"
#include "utilities.h"
#include <filesystem>
#include <fstream>
#include <cctype>


bool Chargeur::loaded_ = false;
std::map<std::string, std::string, caseInsensitiveCompare> Chargeur::location_ = 
    std::map<std::string, std::string, caseInsensitiveCompare>();

Chargeur::Chargeur() 
{
    // Si l'initialisation est faite, on ne fait rien
    if(!loaded_)
    {
        loaded_ = true;

        std::ifstream liste(RessourceFinder::getPath("Data/chemins.ini"));
        if(!liste.is_open())
            throw std::runtime_error("Fichier rc/Data/chemins.ini non trouvé");
        while(!liste.eof())
        {
            std::string ligne;
            std::getline(liste, ligne);
            
            // On enlève les commentaires
            const auto pos = ligne.find('#');
            if(pos != std::string::npos)
                ligne.erase(pos);
            
            auto tokens = tokenize(ligne, '=');
            tokens.first = trim(tokens.first);
            tokens.second = trim(tokens.second);
            
            if(!tokens.first.empty() && !tokens.second.empty())
                location_.insert({tokens.first, tokens.second});
        }
    }
}

//TODO PG je crois qu'on ne peut pas appeler de sous-texture là, si on appelle une 2ème sous texture sur une image de chemins.ini qui a déjà été chargée ça va renvoyer la même...
//TODO PG sous-texture
std::shared_ptr<sf::Texture> Chargeur::getTexture(const std::string& name, bool repeated, bool smooth, const sf::IntRect& area) {
    if (textures_.find(name) != textures_.end())
        return textures_.at(name);

    if (location_.find(name) == location_.end())
        throw std::runtime_error("Unknown location of texture " + name);

    auto t = std::make_shared<sf::Texture>();
    if (!t->loadFromFile(RessourceFinder::getPath(location_[name]), area))
        throw std::runtime_error("Can't load " + location_[name]);
    else {
        t->setRepeated(repeated);
        t->setSmooth(smooth);
    }

    textures_[name] = t;

    return textures_.at(name);
}


std::shared_ptr<sf::SoundBuffer> Chargeur::getSoundBuffer(const std::string& name) {
    if (sound_buffers_.find(name) != sound_buffers_.end())
        return sound_buffers_.at(name);

    if (location_.find(name) == location_.end())
        throw std::runtime_error("Unknown location of soundbuffer " + name);

    auto t = std::make_shared<sf::SoundBuffer>();
    if (!t->loadFromFile(RessourceFinder::getPath(location_[name])))
        throw std::runtime_error("Can't load " + location_[name]);

    sound_buffers_[name] = t;

    return sound_buffers_.at(name);
}

std::shared_ptr<sf::Font> Chargeur::getFont(const std::string& name) {
    if (fonts_.find(name) != fonts_.end())
        return fonts_.at(name);

    if (location_.find(name) == location_.end())
        throw std::runtime_error("Unknown location of font " + name);

    auto t = std::make_shared<sf::Font>();
    if (!t->loadFromFile(RessourceFinder::getPath(location_[name])))
        throw std::runtime_error("Can't load " + location_[name]);

    fonts_[name] = t;

    return fonts_.at(name);
}

void Chargeur::playSoundAtDeath(const std::string & name)
{
	if (!sound_buffers_[name])
		throw std::runtime_error("Sound \"" + name + "\" not loaded.");
	if (sounds_at_death_.find(name) == sounds_at_death_.end())
		sounds_at_death_.emplace(name, *sound_buffers_[name]);
	sounds_at_death_.at(name).play();
}

bool caseInsensitiveCompare::operator()(const std::string& a, const std::string& b) const
{
    auto first1 = a.begin();
    auto first2 = b.begin();
    const auto last1 = a.end();
    const auto last2 = b.end();

    while(first1 != last1 && first2 != last2)
    {
        if (tolower(*first1) < tolower(*first2))
            return true;
        else if (tolower(*first1) > tolower(*first2))
            return false;
        ++first1;
        ++first2;
    }
    return first1 == last1 && first2 != last2;
}

std::string RessourceFinder::getPath(std::string const& name) {
    if (!RessourceFinder::instance().wdSet) {
        using namespace std::filesystem;
        path p = current_path();
        while (!exists(p / "rc") && p.has_parent_path())
            p = p.parent_path();
        if (exists(p / "rc"))
            current_path(p);
        else
            throw std::runtime_error("Can't find resources directory.");
        RessourceFinder::instance().wdSet = true;
    }
    return "rc/" + name;
}

RessourceFinder& RessourceFinder::instance() {
    static RessourceFinder instance;
    return instance;
}


