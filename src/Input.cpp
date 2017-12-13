#include "Input.h"
#include <cmath>


template<size_t N>
Input_base<N>::Input_base(Media m)
{
    switch(m)
    {
        case Media::Keyboard:
            init_default_keyboard();
            break;

        case Media::Joypad:
            init_default_joypad();
            break;

        default:
            break;
    }
}


template<size_t N>
void Input_base<N>::init_default_keyboard()
{
    movement_media_ = Media::Keyboard;
    movement_input_.keyboard_ = {sf::Keyboard::Up,
                                 sf::Keyboard::Down,
                                 sf::Keyboard::Left,
                                 sf::Keyboard::Right};
}


template<size_t N>
void Input_base<N>::init_default_joypad()
{
    movement_media_ = Media::Joypad;
    movement_input_.joypad_.input_type_ = movement_input_t::joypad_t::Joystick;
    movement_input_.joypad_.joypad_input_.joysticks_ = typename movement_input_t::joypad_t::joypad_input_t::joysticks_t();

    unsigned int id = 0;
    while(!sf::Joystick::isConnected(id) && id < 7)
        id++;

    if(sf::Joystick::isConnected(id))
    {
        movement_input_.joypad_.joypad_id_ = id;
        if(sf::Joystick::hasAxis(id, sf::Joystick::Axis::X))
            movement_input_.joypad_.joypad_input_.joysticks_.left_right_axis_ = sf::Joystick::Axis::X;
        if(sf::Joystick::hasAxis(id, sf::Joystick::Axis::Y))
            movement_input_.joypad_.joypad_input_.joysticks_.up_down_axis_ = sf::Joystick::Axis::Y;
    }
}


template<size_t N>
sf::Vector2f Input_base<N>::move(float max_speed, const sf::Time& elapsed_time, const sf::Vector2f& ratio)
{
    switch(movement_media_)
    {
        case Media::Keyboard:
            return move_keyboard(max_speed, elapsed_time);

        case Media::Joypad:
            return move_joypad(max_speed, elapsed_time);

        default:
            return {0, 0};
    }
}


template<size_t N>
sf::Vector2f Input_base<N>::move_keyboard(float max_speed, const sf::Time& elapsed_time)
{
    bool up, down, left, right;
    up = movement_input_.keyboard_.up_key_ && sf::Keyboard::isKeyPressed(movement_input_.keyboard_.up_key_.value());
    down = movement_input_.keyboard_.down_key_ && sf::Keyboard::isKeyPressed(movement_input_.keyboard_.down_key_.value());
    left = movement_input_.keyboard_.left_key_ && sf::Keyboard::isKeyPressed(movement_input_.keyboard_.left_key_.value());
    right = movement_input_.keyboard_.right_key_ && sf::Keyboard::isKeyPressed(movement_input_.keyboard_.right_key_.value());

    // Si on a les deux côtés opposés, on annule
    if(up && down)
        up = down = false;
    if(left && right)
        left = right = false;

    int nb = up + down + left + right;

    if(!up && !down && !left && !right)
        return {0, 0};

    return {(right - left) * max_speed / sqrt(nb) * elapsed_time.asSeconds(), (down - up ) * max_speed / sqrt(nb) * elapsed_time.asSeconds()};
}


template<size_t N>
sf::Vector2f Input_base<N>::move_joypad(float max_speed, const sf::Time& elapsed_time)
{
    unsigned int id;
    if(movement_input_.joypad_.joypad_id_ && sf::Joystick::isConnected(id = movement_input_.joypad_.joypad_id_.value()))
    {
        if(movement_input_.joypad_.input_type_ == movement_input_t::joypad_t::Joystick)
        {
            float dx = 0, dy = 0;
            if(movement_input_.joypad_.joypad_input_.joysticks_.left_right_axis_)
                dx = sf::Joystick::getAxisPosition(id, movement_input_.joypad_.joypad_input_.joysticks_.left_right_axis_.value());
            if(movement_input_.joypad_.joypad_input_.joysticks_.up_down_axis_)
                dy = sf::Joystick::getAxisPosition(id, movement_input_.joypad_.joypad_input_.joysticks_.up_down_axis_.value());

            if(dx == 0 && dy == 0)
                return {0, 0};

            dx *= max_speed / 100 * elapsed_time.asSeconds() * (movement_input_.joypad_.joypad_input_.joysticks_.left_right_dir_.value_or(false) ? -1 : 1);
            dy *= max_speed / 100 * elapsed_time.asSeconds() * (movement_input_.joypad_.joypad_input_.joysticks_.up_down_dir_.value_or(false) ? -1 : 1);

            return {dx*abs(dx) / sqrt(dx*dx + dy*dy), dy*abs(dy) / sqrt(dx*dx + dy*dy)};
        }
    }

    return {0, 0};
}