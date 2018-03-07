#include "bindings.h"


void set_keyboard_default_binding_1(Input& in)
{
    in.set_movement_mode(Input::Media::Keyboard);
    in.set_action_keyboard(PAUSE, sf::Keyboard::Escape);
    in.set_action_keyboard(TIR1, sf::Keyboard::W);
    in.set_action_keyboard(TIR2, sf::Keyboard::X);
    in.set_action_keyboard(COMP1, sf::Keyboard::Q);
    in.set_action_keyboard(COMP2, sf::Keyboard::S);
    in.set_action_keyboard(COMP3, sf::Keyboard::D);
    in.set_action_keyboard(ULTI, sf::Keyboard::C);
}


void set_keyboard_default_binding_2(Input& in)
{
	in.set_movement_mode(Input::Media::Keyboard);
	in.set_action_keyboard(PAUSE, sf::Keyboard::Escape);
	in.set_action_keyboard(TIR1, sf::Keyboard::F);
	in.set_action_keyboard(TIR2, sf::Keyboard::D);
	in.set_action_keyboard(COMP1, sf::Keyboard::A);
	in.set_action_keyboard(COMP2, sf::Keyboard::Z);
	in.set_action_keyboard(COMP3, sf::Keyboard::E);
	in.set_action_keyboard(ULTI, sf::Keyboard::R);
}

void set_mouse_default_binding(Input& in)
{
    in.set_movement_mode(Input::Media::Mouse);
    in.set_action_keyboard(PAUSE, sf::Keyboard::Escape);
    in.set_action_mouse(TIR1, sf::Mouse::Left);
    in.set_action_mouse(TIR2, sf::Mouse::Right);
    in.set_action_keyboard(COMP1, sf::Keyboard::A);
	in.set_action_keyboard(COMP2, sf::Keyboard::Z);
	in.set_action_keyboard(COMP3, sf::Keyboard::E);
	in.set_action_keyboard(ULTI, sf::Keyboard::R);
}

void set_joypad_default_binding(Input& in)
{
    in.set_movement_mode(Input::Media::Joypad);
}
