#include "Divers.h"
#include "../constantes.h"
#include <SFML/Graphics.hpp>


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