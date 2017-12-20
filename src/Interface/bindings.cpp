#include "bindings.h"


void set_keyboard_binding(Input& in)
{
    in.set_ation_keyboard(0, sf::Keyboard::W);
    in.set_ation_keyboard(1, sf::Keyboard::X);
}
