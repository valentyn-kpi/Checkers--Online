//
// Created by valen on 5/4/2023.
//

#include "SceneManager.h"

/**
 * Додає сцену до менеджера сцен
 * @param scene вказівник на сцену
 */
void SceneManager::addScene(Scene* scene) {
    scenes.push_back(scene);
}

/**
 * Перемикає на сцену з індексом index
 * @param index індекс сцени
 */
void SceneManager::switchToScene(int index) {
    if (index >= 0 && index < scenes.size()) {
        if (currentSceneIndex >= 0 && currentSceneIndex < scenes.size()) {
            scenes[currentSceneIndex]->onExit();
        }
        currentSceneIndex = index;
        scenes[currentSceneIndex]->onEnter();
    }
}

/**
 * Оновлює поточну сцену
 * @param deltaTime час між кадрами
 */
void SceneManager::updateCurrentScene(int deltaTime) {
    if (currentSceneIndex >= 0 && currentSceneIndex < scenes.size()) {
        scenes[currentSceneIndex]->update(deltaTime);
    }
}

/**
 * Малює поточну сцену
 * @param target вікно
 */
void SceneManager::drawCurrentScene(sf::RenderWindow &target) {
    if (currentSceneIndex >= 0 && currentSceneIndex < scenes.size()) {
        scenes[currentSceneIndex]->draw(target);
    }
}

/**
 * Обробляє подію
 * @param event подія
 */
void SceneManager::handleEvent(const sf::Event &event) {
    if (currentSceneIndex >= 0 && currentSceneIndex < scenes.size()) {
        scenes[currentSceneIndex]->handleEvent(event);
    }
}