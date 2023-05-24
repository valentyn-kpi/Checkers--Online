//
// Created by valen on 5/4/2023.
//

#include <cmath>
#include <iostream>
#include "Button.h"

/**
 * Конструктор класа Button
 * @param window - Вікно, на якому буде відображатися кнопка
 * @param text - Текст кнопки
 * @param position - Позиція кнопки
 * @param context - Контекст, з якого було викликано кнопку
 * @param onClick - Функція, яка буде викликатися при натисканні на кнопку
 * @param text_color_default - Колір тексту кнопки, коли вона не натиснута
 * @param text_color_pressed - Колір тексту кнопки, коли вона натиснута
 * @param outline_color - Колір обведення кнопки
 */
Button::Button(sf::RenderWindow &window, const std::string &text,
               sf::Vector2f position, void *context, void (*onClick)(void *),
               sf::Color text_color_default,
               sf::Color text_color_pressed,
               sf::Color outline_color) {
    font.loadFromFile("res/fonts/JBB.ttf");

    this->button_text.setString(text);
    this->button_text.setFont(font);
    this->button_text.setCharacterSize((unsigned int) round(std::min(window.getSize().x, window.getSize().y) * 0.05));
    this->button_text.setOrigin(this->button_text.getGlobalBounds().width / 2.0f, this->button_text.getGlobalBounds().height / 2.0f);
    this->button_text.setPosition(position);
    this->button_text.setFillColor(text_color_default);
    this->button_text.setOutlineColor(outline_color);
    this->button_text.setOutlineThickness(0);
    this->text_color_default = text_color_default;
    this->text_color_pressed = text_color_pressed;

    if (!hoverSoundBuffer.loadFromFile("res/audio/click.wav")) {
        // handle error loading sound file
    }
    this->onClick = onClick;
    this->context = context;
    this->window = &window;
}

/**
 * Метод, який відображає кнопку на вікні
 */
void Button::draw() {
    window->draw(this->button_text);
}

/**
 * Метод, який оновлює стан кнопки в залежності від позиції миші
 * @param mouse_position - Позиція миші
 */
void Button::update(sf::Vector2f mouse_position) {
    if (this->button_text.getGlobalBounds().contains(mouse_position) && !slide_detected) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            is_pressed = true;
            this->button_text.setFillColor(this->text_color_pressed);
        } else if (is_pressed) {
            is_pressed = false;
            this->button_text.setFillColor(this->text_color_default);
            if (this->onClick != nullptr) {
                this->onClick(context);
            }
        } else {
            this->button_text.setOutlineThickness(4);
            if (hoverSound.getStatus() != sf::Sound::Playing && !played) {
                hoverSound.setBuffer(hoverSoundBuffer);
                hoverSound.setPlayingOffset(sf::seconds(0.005f));
                hoverSound.play();
                played = true;
            }
        }
    } else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        slide_detected = true;
        this->is_pressed = false;
        this->played = false;
        this->button_text.setOutlineThickness(1);
        this->button_text.setFillColor(this->text_color_default);
    } else {
        this->played = false;
        slide_detected = false;
        this->is_pressed = false;
        this->button_text.setOutlineThickness(1);
        this->button_text.setFillColor(this->text_color_default);
    }
}

/**
 * Метод, який повертає розмір шрифту тексту кнопки
 * @return Розмір шрифту тексту кнопки
 */
unsigned int Button::getCharterSize() const {
    return this->button_text.getCharacterSize();
}

/**
 * Метод який повертає позицію кнопки
 */
sf::Vector2f Button::getPosition() const {
    return this->button_text.getPosition();
}