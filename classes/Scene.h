//
// Created by valen on 5/3/2023.
//

#ifndef CHECKERS_SCENE_H
#define CHECKERS_SCENE_H

#include "SFML/Graphics.hpp"

/**
 * Клас Scene базовий клас для сцен
 */
class Scene {
public:
    /**
     * Віртуальний метод для оновлення сцени, має бути перевизначений в дочірніх класах
     */
    virtual void update(int deltaTime) = 0;
    /**
     * Віртуальний метод для відображення сцени, має бути перевизначений в дочірніх класах
     */
    virtual void draw(sf::RenderWindow &target) = 0;
    /**
     * Віртуальний метод для обробки подій, має бути перевизначений в дочірніх класах
     */
    virtual void handleEvent(const sf::Event &event) = 0;
    /**
     * Віртуальний метод для обробки входу в сцену, має бути перевизначений в дочірніх класах
     */
    virtual void onEnter() = 0;
    /**
     * Віртуальний метод для обробки виходу з сцени, має бути перевизначений в дочірніх класах
     */
    virtual void onExit() = 0;
};

#endif //CHECKERS_SCENE_H
