//
// Created by valen on 5/4/2023.
//

#ifndef CHECKERS_SCENEMANAGER_H
#define CHECKERS_SCENEMANAGER_H

#include "Scene.h"

/**
 * Клас SceneManager об'єктами якого є менеджер сцен
 */
class SceneManager {
public:
    void addScene(Scene *scene);

    void switchToScene(int index);

    void updateCurrentScene(int deltaTime);

    void drawCurrentScene(sf::RenderWindow &target);

    void handleEvent(const sf::Event &event);

private:
    std::vector<Scene *> scenes;
    int currentSceneIndex = -1;
};

#endif //CHECKERS_SCENEMANAGER_H
