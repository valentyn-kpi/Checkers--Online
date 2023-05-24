//
// Created by valen on 5/4/2023.
//

#ifndef CHECKERS_BUTTON_H
#define CHECKERS_BUTTON_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

//TODO: під час переробки видалити виклик функції при натисканні на кнопку, додати методи isPressed(), isHovered() etc...

/**
 * Клас Button, об'єкт якого представляє собою кнопку з тексту.
 */
class Button {
public:
    Button(sf::RenderWindow &window, const std::string &text,
           sf::Vector2f position, void *context, void (*onClick)(void *) = nullptr,
           sf::Color text_color_default = sf::Color::White,
           sf::Color text_color_pressed = sf::Color(87, 242, 135),
           sf::Color outline_color = sf::Color(114, 137, 218));

    void draw();

    //get charter size
    unsigned int getCharterSize() const;

    //get position
    sf::Vector2f getPosition() const;

    void update(sf::Vector2f mouse_position);


private:
    void (*onClick)(void *) = nullptr;

    void *context = nullptr;
    sf::RenderWindow *window = nullptr;
    sf::Text button_text;
    sf::Color text_color_default = sf::Color::White;
    sf::Color text_color_pressed = sf::Color::Green;
    sf::Sound hoverSound;
    sf::SoundBuffer hoverSoundBuffer;
    sf::Font font;
    bool is_pressed = false;
    bool slide_detected = false;
    bool played = false;
};


#endif //CHECKERS_BUTTON_H
