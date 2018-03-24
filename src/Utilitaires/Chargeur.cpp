#include "Chargeur.h"
#include "../constantes.h"
#include "Divers.h"
#include <fstream>
#include <cctype>
#include <iostream>


bool Chargeur::loaded_ = false;
std::map<std::string, std::string> Chargeur::location_ = std::map<std::string, std::string>();

Chargeur::Chargeur() 
{
    // Si l'initialisation est faite, on ne fait rien
    if(!loaded_)
    {
        loaded_ = true;
        
        std::ifstream liste(chemin_rc "Data/chemins.ini");
        if(!liste.is_open())
            throw std::runtime_error("Fichier " chemin_rc "Data/chemins.ini non trouvé");
        while(!liste.eof())
        {
            std::string ligne;
            std::getline(liste, ligne);
            
            // On enlève les commentaires
            auto pos = ligne.find('#');
            if(pos != std::string::npos)
                ligne.erase(pos);
            
            auto tokens = tokenize(ligne, '=');
            tokens.first = trim(tokens.first);
            tokens.second = trim(tokens.second);
            
            if(!tokens.first.empty() and !tokens.second.empty())
                location_.insert({tokens.first, tokens.second});
        }
    }
}


std::shared_ptr<sf::Texture> Chargeur::getTexture(const std::string& name)
{
    if(textures_.find(name) != textures_.end())
        return textures_.at(name);

    if(location_.find(name) == location_.end())
        throw std::runtime_error("Unknown location of texture " + name);

    auto t = std::make_shared(new sf::Texture);
    if(!t->loadFromFile(location_[name]))
        throw std::runtime_error("Can't load "+location_[name]);

    textures_[name] = t;

    return textures_.at(name);
}


std::shared_ptr<sf::SoundBuffer> Chargeur::getSoundBuffer(const std::string& name)
{
    if(sound_buffers_.find(name) != sound_buffers_.end())
        return sound_buffers_.at(name);

    if(location_.find(name) == location_.end())
        throw std::runtime_error("Unknown location of soundbuffer " + name);

    auto t = std::make_shared(new sf::SoundBuffer);
    if(!t->loadFromFile(location_[name]))
        throw std::runtime_error("Can't load "+location_[name]);

    sound_buffers_[name] = t;

    return sound_buffers_.at(name);
}
