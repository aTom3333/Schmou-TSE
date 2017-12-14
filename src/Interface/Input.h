#ifndef INPUT_H
#define INPUT_H

#include <SFML/Graphics.hpp>
#include <optional>



template<size_t N>
class Input_base
{
    public:
        enum class Media
        {
            Keyboard, Joypad, Mouse, Touchscreen
        };

        sf::Vector2f move(float max_speed, const sf::Time& elapsed_time);

        explicit Input_base(const sf::RenderWindow& w, Media m = Media::Keyboard);

    private:
        void init_default_keyboard();
        void init_default_joypad();
        void init_default_mouse();
        sf::Vector2f move_keyboard(float max_speed, const sf::Time& elapsed_time);
        sf::Vector2f move_joypad(float max_speed, const sf::Time& elapsed_time);
        sf::Vector2f move_mouse(float max_speed, const sf::Time& elapsed_time);

        const sf::RenderWindow& window_;
        Media movement_media_; // Par quoi est géré le déplacement
        /// @cond NO_DOC_PRIVATE_CLASSES
        union movement_input_t {
            movement_input_t() {keyboard_ = {sf::Keyboard::Up,
                                             sf::Keyboard::Down,
                                             sf::Keyboard::Left,
                                             sf::Keyboard::Right};}
            struct keyboard_t {
                // Movement Keyboard binding
                std::optional<sf::Keyboard::Key> up_key_;
                std::optional<sf::Keyboard::Key> down_key_;
                std::optional<sf::Keyboard::Key> left_key_;
                std::optional<sf::Keyboard::Key> right_key_;
            } keyboard_;
            struct joypad_t {
                // Movement Joystick binding
                std::optional<unsigned int> joypad_id_;
                enum input_type_t { Joystick, Button } input_type_;
                union joypad_input_t {
                    joypad_input_t() {joysticks_ = joysticks_t();}
                    struct buttons_t {
                        std::optional<unsigned int> up_button_;
                        std::optional<unsigned int> down_button_;
                        std::optional<unsigned int> left_button_;
                        std::optional<unsigned int> right_button_;
                    } buttons_;
                    struct joysticks_t {
                        std::optional<sf::Joystick::Axis> up_down_axis_;
                        std::optional<bool> up_down_dir_;
                        std::optional<sf::Joystick::Axis> left_right_axis_;
                        std::optional<bool> left_right_dir_;
                    } joysticks_;
                } joypad_input_;
            } joypad_;
            struct mouse_t {
                std::optional<sf::Vector2f> last_pos_;
            } mouse_;
        } movement_input_;
        /// @endcond

};

using Input = Input_base<0>; // C'est ici qu'on choisit le nombre d'actions qu'on veut

#endif // INPUT_H
