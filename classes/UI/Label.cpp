//
// Created by valen on 5/4/2023.
//

#include <iostream>
#include "Label.h"

/**
 * Конструктор класу Label
 * @param position - позиція текстового поля
 * @param text - текст який буде виведений
 * @param window - вікно в яке буде виведений текст
 * @param size - розмір тексту
 */
Label::Label(sf::Vector2f position, const std::string &text, sf::RenderWindow &window, int size) {
    if (!font.loadFromFile("res/fonts/JBB.ttf")) {
        std::cout << "Error loading font" << std::endl;
    }

    this->text.setFont(font);
    this->text.setString(text);
    this->text.setCharacterSize(size);
    this->text.setOrigin(this->text.getGlobalBounds().width / 2, this->text.getGlobalBounds().height / 2);
    this->text.setOutlineThickness(3);
    this->text.setPosition(position);
    this->target = &window; // Make sure window is a valid sf::RenderWindow object
}

/**
 * Метод який виводить текстове поле
 */
void Label::draw() {
   target->draw(text);
}

/**
 * Метод який встановлює текст
 * @param text1 - текст який буде виведений
 */
void Label::setText(const std::string &text1) {
    this->text.setString(text1);
    this->text.setOrigin(this->text.getGlobalBounds().width / 2, this->text.getGlobalBounds().height / 2);
}

/**
 * Метод який встановлює позицію текстового поля
 * @param position - позиція текстового поля
 */
void Label::setPosition(sf::Vector2f position) {
    this->text.setPosition(position);
}

/**
 * Метод який встановлює розмір тексту
 * @param size - розмір тексту

void Label::setCharacterSize(int size) {
    this->text.setCharacterSize(size);
    this->text.setOrigin(this->text.getGlobalBounds().width / 2, this->text.getGlobalBounds().height / 2);
}
*/

/**
 * Метод який встановлює колір тексту
 * @param color - колір тексту
 */
void Label::setFillColor(sf::Color color) {
    this->text.setFillColor(color);
}

/**
 * Метод який встановлює колір обводки тексту
 * @param color - колір обводки тексту
 */
void Label::setOutlineColor(sf::Color color) {
    this->text.setOutlineColor(color);
}

/**
 * Метод який встановлює товщину обводки тексту
 * @param thickness - товщина обводки тексту
 */
void Label::setOutlineThickness(float thickness) {
    this->text.setOutlineThickness(thickness);

}

/**
 * Метод який повертає позицію текстового поля
 * @return позиція текстового поля
 */
sf::Vector2f Label::getPosition() {
    return this->text.getPosition();
}

/**
 * Метод який повертає глобальні межі текстового поля
 * @return глобальні межі текстового поля
 */
sf::FloatRect Label::getGlobalBounds() {
    return this->text.getGlobalBounds();
}


