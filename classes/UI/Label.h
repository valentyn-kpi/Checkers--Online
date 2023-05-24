//
// Created by valen on 5/4/2023.
//

#ifndef CHECKERS_LABEL_H
#define CHECKERS_LABEL_H
#include <SFML/Graphics.hpp>

/**
 * Клас Label об'єктами якого є текстові поля
 */
class Label {
public:
    Label(sf::Vector2f position, const std::string& text, sf::RenderWindow &window, int size = 30);

    void draw();

    void setText(const std::string& text1);

    void setPosition(sf::Vector2f position);

    void setCharacterSize(int size);

    void setFillColor(sf::Color color);

    void setOutlineColor(sf::Color color);

    void setOutlineThickness(float thickness);

    sf::Vector2f getPosition();

    sf::FloatRect getGlobalBounds();
private:
    sf::Text text;
    sf::Font font;
    sf::RenderWindow *target = nullptr;
};


#endif //CHECKERS_LABEL_H
