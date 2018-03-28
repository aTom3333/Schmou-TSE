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
            
            if(!tokens.first.empty() && !tokens.second.empty())
                location_.insert({tokens.first, tokens.second});
        }
    }
}

//TODO PG je crois qu'on ne peut pas appeler de sous-texture là, si on appelle une 2ème sous texture sur une image de chemins.ini qui a déjà été chargée ça va renvoyer la même...
std::shared_ptr<sf::Texture> Chargeur::getTexture(const std::string& name, const bool& repeated, const bool& smooth, const sf::IntRect& area)
{
    if(textures_.find(name) != textures_.end())
        return textures_.at(name);

    if(location_.find(name) == location_.end())
        throw std::runtime_error("Unknown location of texture " + name);

    std::shared_ptr<sf::Texture> t(new sf::Texture);
    if(!t->loadFromFile(location_[name],area))
		throw std::runtime_error("Can't load " + location_[name]);
	else {
		t->setRepeated(repeated);
		t->setSmooth(smooth);
	}

    textures_[name] = t;

    return textures_.at(name);
}


std::shared_ptr<sf::SoundBuffer> Chargeur::getSoundBuffer(const std::string& name)
{
    if(sound_buffers_.find(name) != sound_buffers_.end())
        return sound_buffers_.at(name);

    if(location_.find(name) == location_.end())
        throw std::runtime_error("Unknown location of soundbuffer " + name);

    std::shared_ptr<sf::SoundBuffer> t(new sf::SoundBuffer);
    if(!t->loadFromFile(location_[name]))
        throw std::runtime_error("Can't load "+location_[name]);

    sound_buffers_[name] = t;

    return sound_buffers_.at(name);
}

std::shared_ptr<sf::Font> Chargeur::getFont(const std::string& name)
{
	if (sound_buffers_.find(name) != sound_buffers_.end())
		return fonts_.at(name);

	if (location_.find(name) == location_.end())
		throw std::runtime_error("Unknown location of font " + name);

	std::shared_ptr<sf::SoundBuffer> t(new sf::SoundBuffer);
	if (!t->loadFromFile(location_[name]))
		throw std::runtime_error("Can't load " + location_[name]);

	sound_buffers_[name] = t;

	return fonts_.at(name);
}

