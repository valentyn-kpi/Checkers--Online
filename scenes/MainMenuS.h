//
// Created by valen on 5/4/2023.
//

#ifndef CHECKERS_MAINMENUS_H
#define CHECKERS_MAINMENUS_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../classes/GameBoard.h"
#include "../classes/Scene.h"
#include "../classes/Settings.h"
#include "../classes/UI/Menu.h"
#include "../classes/SceneManager.h"

class MainMenuS : public Scene {
public:
    MainMenuS(sf::RenderWindow &window, Settings &settings, SceneManager &sceneManager);
    void update(int deltaTime) override;
    void draw(sf::RenderWindow &target) override;
    void handleEvent(const sf::Event &event) override;
    void onEnter() override;
    void onExit() override;

    void startOfflineGame();

    void startOnlineGame();

    void openSettings();

    void exitGame();

    void openAbout();

private:
    void reconstructMenu();
    SceneManager *sceneManager;
    sf::RenderWindow *window;
    sf::RenderTexture *renderTexture;
    sf::Sprite *renderSprite;
    Settings *settings;
    sf::Sprite background;
    Menu scene_menu;
    GameBoard *gameBoard;

    bool menu_event = false;
    int timer = 0;

    void renderBoard();

    long long test = 0;
};


#endif //CHECKERS_MAINMENUS_H
