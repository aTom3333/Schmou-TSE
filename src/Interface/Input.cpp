#include "Input.h"
#include <cmath>


template<size_t N>
Input_base<N>::Input_base(const sf::RenderWindow& w, Media media) : window_{w}
{
    switch(media)
    {
        case Media::Keyboard:
            init_default_keyboard();
            break;

        case Media::Joypad:
            init_default_joypad();
            break;

        case Media::Mouse:
            init_default_mouse();
            break;

        default:
            break;
    }
}
/*
template<size_t N>
Input_base<N>::Input_base(const Input_base& other) : 
    window_{other.window_},
    

{

}*/



template<size_t N>
void Input_base<N>::init_default_keyboard()
{
    set_default_movement_keyboard();

    for(size_t i = 0; i < N; ++i)
    {
        actions_[i].action_media_ = Media::Keyboard;
        actions_[i].binding_.keyboard_key_ = nullopt;
    }
}


template<size_t N>
void Input_base<N>::init_default_joypad()
{
    set_default_movement_joypad();

    for(size_t i = 0; i < N; ++i)
    {
        actions_[i].action_media_ = Media::Joypad;
        actions_[i].binding_.joypad_button_ = nullopt;
    }
}


template<size_t N>
void Input_base<N>::init_default_mouse()
{
    movement_media_ = Media::Mouse;
    movement_input_.mouse_ = {};

    for(size_t i = 0; i < N; ++i)
    {
        actions_[i].action_media_ = Media::Mouse;
        actions_[i].binding_.mouse_button_ = nullopt;
    }
}


template<size_t N>
sf::Vector2f Input_base<N>::move(float max_speed, const sf::Time& elapsed_time)
{
    switch(movement_media_)
    {
        case Media::Keyboard:
            return move_keyboard(max_speed, elapsed_time);

        case Media::Joypad:
            return move_joypad(max_speed, elapsed_time);

        case Media::Mouse:
            return move_mouse(max_speed, elapsed_time);

        default:
            return {0, 0};
    }
}


template<size_t N>
sf::Vector2f Input_base<N>::move_keyboard(float max_speed, const sf::Time& elapsed_time)
{
    bool up = movement_input_.keyboard_.up_key_ && sf::Keyboard::isKeyPressed(movement_input_.keyboard_.up_key_.value()),
         down = movement_input_.keyboard_.down_key_ && sf::Keyboard::isKeyPressed(movement_input_.keyboard_.down_key_.value()),
         left = movement_input_.keyboard_.left_key_ && sf::Keyboard::isKeyPressed(movement_input_.keyboard_.left_key_.value()),
         right = movement_input_.keyboard_.right_key_ && sf::Keyboard::isKeyPressed(movement_input_.keyboard_.right_key_.value());
	
    // Si on a les deux côtés opposés, on annule
	//TODO il serait plus agréable (affordant) que le côté opposé pressé en dernier soit prioritaire car là si on appuie sur les deux en même temps le vaisseau s'arrête et c'est contre-intuitif. Mais ce n'est pas possible si on fait comme ça, il faudrait récupérer les évènement pour savoir à quel instant quelle touche est pressée alors que là, on ne fait que récupérer l'état du clavier à l'instant t. Eh bien c'est très simple on créer un vector d'inputs qui gare en mémoire les actions effectuées depuis x secondes ohohoh
    if(up && down)
        up = down = false;
    if(left && right)
        left = right = false;

    if(!up && !down && !left && !right)
        return {0, 0};

    const int nb = up + down + left + right;

    return {(right - left) * max_speed / static_cast<float>(sqrt(nb)) * elapsed_time.asSeconds(), (down - up ) * max_speed / static_cast<float>(sqrt(nb)) * elapsed_time.asSeconds()};
}


template<size_t N>
sf::Vector2f Input_base<N>::move_joypad(float max_speed, const sf::Time& elapsed_time)
{
    unsigned int id;
    if(joypad_id_ && sf::Joystick::isConnected(id = joypad_id_.value()))
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

            return {static_cast<float>(dx*abs(dx) / hypot(dx, dy)), 
                    static_cast<float>(dy*abs(dy) / hypot(dx, dy))};
        }
        else if(movement_input_.joypad_.input_type_ == movement_input_t::joypad_t::Button)
        {
            bool up = movement_input_.joypad_.joypad_input_.buttons_.up_button_
                    && sf::Joystick::isButtonPressed(id, movement_input_.joypad_.joypad_input_.buttons_.up_button_.value());
            bool down = movement_input_.joypad_.joypad_input_.buttons_.down_button_
                    && sf::Joystick::isButtonPressed(id, movement_input_.joypad_.joypad_input_.buttons_.down_button_.value());
            bool left = movement_input_.joypad_.joypad_input_.buttons_.left_button_
                    && sf::Joystick::isButtonPressed(id, movement_input_.joypad_.joypad_input_.buttons_.left_button_.value());
            bool right = movement_input_.joypad_.joypad_input_.buttons_.right_button_
                    && sf::Joystick::isButtonPressed(id, movement_input_.joypad_.joypad_input_.buttons_.right_button_.value());

            // Si on a les deux côtés opposés, on annule
            if(up && down)
                up = down = false;
            if(left && right)
                left = right = false;

            if(!up && !down && !left && !right)
                return {0, 0};

            const int nb = up + down + left + right;

            return {(right - left) * max_speed / static_cast<float>(sqrt(nb)) * elapsed_time.asSeconds(), (down - up ) * max_speed / static_cast<float>(sqrt(nb)) * elapsed_time.asSeconds()};
        }
    }

    return {0, 0};
}


template<size_t N>
sf::Vector2f Input_base<N>::move_mouse(float max_speed, const sf::Time& elapsed_time)
{
    auto new_pos = window_.mapPixelToCoords(sf::Mouse::getPosition(window_));
    if(!movement_input_.mouse_.last_pos_)
    {
        movement_input_.mouse_.last_pos_ = new_pos;
        return {0, 0};
    }
    auto diff = new_pos - movement_input_.mouse_.last_pos_.value();

    if(diff.x == 0 && diff.y == 0)
        return {0, 0};

    const float dx = diff.x * abs(diff.x) / (diff.x*diff.x + diff.y*diff.y);
    const float dy = diff.y * abs(diff.y) / (diff.x*diff.x + diff.y*diff.y);

    sf::Vector2f delta{dx * max_speed * elapsed_time.asSeconds(), dy * max_speed * elapsed_time.asSeconds()};

    movement_input_.mouse_.last_pos_.value() += delta;

    return delta;
}

template<size_t N>
bool Input_base<N>::action(size_t n) const
{
    if(n > N)
        return false;
    switch(actions_[n].action_media_)
    {
        case Media::Keyboard:
            return action_keyboard(n);

        case Media::Joypad:
            return action_joypad(n);

        case Media::Mouse:
            return action_mouse(n);

        default:
            return false;
    }
}

template<size_t N>
bool Input_base<N>::action_keyboard(size_t n) const
{
    return (actions_[n].binding_.keyboard_key_ && sf::Keyboard::isKeyPressed(actions_[n].binding_.keyboard_key_.value()));
}

template<size_t N>
bool Input_base<N>::action_joypad(size_t n) const
{
    return joypad_id_ && actions_[n].binding_.joypad_button_
           && sf::Joystick::isButtonPressed(joypad_id_.value(),
                                            actions_[n].binding_.joypad_button_.value());
}

template<size_t N>
bool Input_base<N>::action_mouse(size_t n) const
{
    return actions_[n].binding_.mouse_button_ && sf::Mouse::isButtonPressed(actions_[n].binding_.mouse_button_.value());
}

template<size_t N>
bool Input_base<N>::find_next_joypad()
{
    for(unsigned int id = 0; id < 8; ++id)
    {
        if(joypad_availability_.test(id) && sf::Joystick::isConnected(id))
        {
            joypad_id_ = id;
            return true;
        }
    }

    return false;
}

template<size_t N>
void Input_base<N>::free_joypad()
{
    if(joypad_id_)
    {
        joypad_availability_.reset(joypad_id_.value());
        joypad_id_ = nullopt;
    }
}

template<size_t N>
Input_base<N>::~Input_base()
{
    free_joypad();
}

template<size_t N>
bool Input_base<N>::isMoving() const
{
    switch(movement_media_)
    {
        case Media::Keyboard:
            break;

        default:
            break;
    }
    
	return sf::Keyboard::isKeyPressed(movement_input_.keyboard_.up_key_.value()) || sf::Keyboard::isKeyPressed(movement_input_.keyboard_.down_key_.value()) || sf::Keyboard::isKeyPressed(movement_input_.keyboard_.left_key_.value()) || sf::Keyboard::isKeyPressed(movement_input_.keyboard_.right_key_.value());
}

template<size_t N>
void Input_base<N>::set_action_keyboard(size_t n, sf::Keyboard::Key key)
{
    if(n >= N)
        // throw std::out_of_range(""); // with exception
        return; // without
    actions_[n].action_media_ = Media::Keyboard;
    actions_[n].binding_.keyboard_key_ = key;
}

template<size_t N>
void Input_base<N>::set_action_mouse(size_t n, sf::Mouse::Button button)
{
    if(n >= N)
        // throw std::out_of_range(""); // with exception
        return; // without
    actions_[n].action_media_ = Media::Mouse;
    actions_[n].binding_.mouse_button_ = button;
}

template<size_t N>
void Input_base<N>::set_default_movement_keyboard()
{
    movement_media_ = Media::Keyboard;
    movement_input_.keyboard_ = {sf::Keyboard::Up,
                                 sf::Keyboard::Down,
                                 sf::Keyboard::Left,
                                 sf::Keyboard::Right};
}

template<size_t N>
void Input_base<N>::set_default_movement_joypad()
{
    movement_media_ = Media::Joypad;
    movement_input_.joypad_.input_type_ = movement_input_t::joypad_t::Joystick;
    movement_input_.joypad_.joypad_input_.joysticks_ = typename movement_input_t::joypad_t::joypad_input_t::joysticks_t();

    
    if(find_next_joypad())
    {
        if(sf::Joystick::hasAxis(joypad_id_.value(), sf::Joystick::Axis::X))
            movement_input_.joypad_.joypad_input_.joysticks_.left_right_axis_ = sf::Joystick::Axis::X;
        if(sf::Joystick::hasAxis(joypad_id_.value(), sf::Joystick::Axis::Y))
            movement_input_.joypad_.joypad_input_.joysticks_.up_down_axis_ = sf::Joystick::Axis::Y;
    }
}

template<size_t N>
void Input_base<N>::set_movement_mode(Media movement_media)
{
    switch(movement_media)
    {
        case Media::Keyboard:
            set_default_movement_keyboard();
            break;
            
        case Media::Mouse:
            movement_input_.mouse_ = {};
            break;
            
        case Media::Joypad:
            set_default_movement_joypad();
            break;

        default:
            break;
    }
}

template class Input_base<NB_ACTION>;

template <size_t N>
std::bitset<8> Input_base<N>::joypad_availability_;