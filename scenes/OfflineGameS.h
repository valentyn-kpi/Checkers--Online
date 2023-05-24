//
// Created by valen on 5/5/2023.
//

#ifndef CHECKERS_OFFLINEGAMES_H
#define CHECKERS_OFFLINEGAMES_H

#include <SFML/Graphics.hpp>
#include "../classes/Scene.h"
#include "../classes/Settings.h"
#include "../classes/SceneManager.h"
#include "../classes/GameBoard.h"

class OfflineGameS : public Scene {

public:
    OfflineGameS(sf::RenderWindow &window, Settings &settings, SceneManager &sceneManager);

    void update(int deltaTime) override;

    void draw(sf::RenderWindow &target) override;

    void handleEvent(const sf::Event &event) override;

    void onEnter() override;

    void onExit() override;

    void back_onClick();

private:
    SceneManager *sceneManager;
    sf::RenderWindow *window;
    Settings *settings;
    sf::Text text;
    Menu menu;
    GameBoard *gameBoard = nullptr;
    bool menu_event = true;

    void reconstructMenu();
};


#endif //CHECKERS_OFFLINEGAMES_H
