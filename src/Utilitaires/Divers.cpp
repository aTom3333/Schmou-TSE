#include "Divers.h"
#include "../constantes.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cctype>


void adapt_viewport(sf::RenderWindow& window)
{
    auto view = window.getView();
    auto size = window.getSize();
    
    float ratio = (float)size.x / size.y;
    float ratio_normal = ECRAN_L / ECRAN_H;
    
    if(ratio > ratio_normal)
    {
        float proportion = ratio_normal / ratio;
        view.setViewport({(1-proportion)/2, 0, proportion, 1});
    }
    else
    {
        float proportion = ratio / ratio_normal;
        view.setViewport({0, (1-proportion)/2, 1, proportion});
    }
    
    window.setView(view);
}

std::string trim(std::string str)
{
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](int ch) {
        return !std::isspace(ch);
    }));
    str.erase(std::find_if(str.rbegin(), str.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), str.end());
    
    return str;
}

std::pair<std::string, std::string> tokenize(const std::string& str, char sep)
{
    auto pos = str.find(sep);
    
    if(pos == std::string::npos)
        return {str, ""};
    
    auto str1 = str.substr(0, pos);
    auto str2 = str.substr(pos+1);
    
    return {str1, str2};
}
