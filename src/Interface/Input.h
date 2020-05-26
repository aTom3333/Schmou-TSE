#ifndef INPUT_H
#define INPUT_H

#include <SFML/Graphics.hpp>
#include <bitset>
#include "../constantes.h"
#include "../Utilitaires/optional.h"

using std::experimental::optional;
using std::experimental::nullopt;

template<size_t N>
class Input_base
{
    public:
        /**
         * @enum Media
         * @brief Énumération qui contient les types d'entrées supportées
         *
         * Cette énumération contient 4 valeurs qui représentent les 4 types de média qui sont
         * supportés pour les entrées
         */
        enum class Media
        {
            Keyboard, Joypad, Mouse, Touchscreen
        };

        /**
         * @fn Input_base
         * @brief Constructeur de Input_base
         *
         * Constructeur qui initialise l'état de l'objet
         * @param [in] w Une référence vers une sf::RenderWindow qui permet de récupérer des informations sur ses entrées
         * @param [in] m Le type de Media à utiliser pour toutes les actions par défaut, clavier par défaut
         */
        explicit Input_base(const sf::RenderWindow& w, Media m = Media::Keyboard);
    
        /**
         * @fn Input_base
         * @brief Constructeur de copie
         * 
         * Constructeur qui crée un nouvel objet en copiant un autre
         * @param [in] other Un autre Input_base à copier
         */
        //Input_base(const Input_base& other);

        /**
         * @fn ~Input_base
         * @brief Destructeur
         *
         * Destructeur qui se contente de libérer la place si l'objet utilisait une manette
         */
        ~Input_base();

        /**
         * @fn move
         * @brief Renvoie le déplacement que l'état des entrées induit
         *
         * Cette fonction permet de calculer le déplacement qui doit être effectué sur le vaissea d'un joueur
         * (ou sur autre chose) en fonction de l'état des entrées, du temps écoulé et de la vitesse maximale donnée.
         * Cette fonction appelle des spécialisation de la fonction pour chaque Media
         * @param [in] max_speed La vitesse maximale autorisée en pixel/s
         * @param [in] elapsed_time Temps écoulé qui doit être utilisé pour le calcul de la distance
         * @return Un @c sf::Vector2f qui contient le déplacement qui doit être effectué sur les deux axes
         */
        sf::Vector2f move(float max_speed, const sf::Time& elapsed_time, sf::Vector2f const& referencePos);

        /**
         * @fn action
         * @brief Teste si une action est en cours
         *
         * Cette fonction permet de vérifier si une action est en cours, càd si le bouton/la touche qui correspond
         * est pressé
         * @param [in] n Le numéro de l'action à tester
         * @return Un @c bool qui vaut @a true si l'action est en cours et @a false sinon
         */
        bool action(size_t n) const;

		/**
		* @fn isMoving
		* @brief renvoie True si une touche pour se mouvoir est pressée
		*
		* Cette fonction permet de vérifier si on cherche à mouvoir le joueur, quel que soit le Input::Media
		* @return Un @c bool qui vaut @a true si un mouvement est en cours et @a false sinon
		*/
		bool isMoving() const;

		//setters
        void set_action_keyboard(size_t n, sf::Keyboard::Key key);
        void set_action_mouse(size_t n, sf::Mouse::Button button);
        void set_default_movement_keyboard();
        void set_default_movement_joypad();
        void set_movement_mode(Media movement_media);

		//getters
		Media get_media() const { return movement_media_; } //thomas est content


    private:
        bool find_next_joypad();
        void free_joypad();

        void init_default_keyboard();
        void init_default_joypad();
        void init_default_mouse();

        sf::Vector2f move_keyboard(float max_speed, const sf::Time& elapsed_time);
        sf::Vector2f move_joypad(float max_speed, const sf::Time& elapsed_time);
        sf::Vector2f move_mouse(float max_speed, const sf::Time& elapsed_time, sf::Vector2f const& referencePos);

        bool action_keyboard(size_t n) const;
        bool action_joypad(size_t n) const;
        bool action_mouse(size_t n) const;

        static std::bitset<8> joypad_availability_;
        const sf::RenderWindow& window_; ///< Référence vers la fenêtre par rapport à laquelle les entrées sont traitées
        Media movement_media_; ///< Media qui gère le déplacement
        optional<unsigned int> joypad_id_;
        /// @cond NO_DOC_PRIVATE_CLASSES
    
    
        union movement_input_t {
            movement_input_t() {keyboard_ = {sf::Keyboard::Up,
                                             sf::Keyboard::Down,
                                             sf::Keyboard::Left,
                                             sf::Keyboard::Right};}
            ~movement_input_t() = default;
            struct keyboard_t {
                // Movement Keyboard binding
                optional<sf::Keyboard::Key> up_key_;
                optional<sf::Keyboard::Key> down_key_;
                optional<sf::Keyboard::Key> left_key_;
                optional<sf::Keyboard::Key> right_key_;
            } keyboard_;
            struct joypad_t {
                // Movement Joystick binding
                enum input_type_t { Joystick, Button } input_type_;
                union joypad_input_t {
                    joypad_input_t() {joysticks_ = joysticks_t();}
                    struct buttons_t {
                        optional<unsigned int> up_button_;
                        optional<unsigned int> down_button_;
                        optional<unsigned int> left_button_;
                        optional<unsigned int> right_button_;
                    } buttons_;
                    struct joysticks_t {
                        optional<sf::Joystick::Axis> up_down_axis_;
                        optional<bool> up_down_dir_;
                        optional<sf::Joystick::Axis> left_right_axis_;
                        optional<bool> left_right_dir_;
                    } joysticks_;
                } joypad_input_;
            } joypad_;
            struct mouse_t {
            } mouse_;
        } movement_input_;
        struct action_t {
            action_t() = default;
            ~action_t() =default;
            Media action_media_;
            union binding_t {
                binding_t() {}
                ~binding_t() {};
                optional<sf::Keyboard::Key> keyboard_key_;
                optional<unsigned int> joypad_button_;
                optional<sf::Mouse::Button> mouse_button_;
            } binding_;
        };
        action_t actions_[N];
        /// @endcond
};

using Input = Input_base<NB_ACTION>;

#endif // INPUT_H
