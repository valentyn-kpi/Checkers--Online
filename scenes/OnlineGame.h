//
// Created by valen on 5/21/2023.
//

#ifndef CHECKERS_ONLINEGAME_H
#define CHECKERS_ONLINEGAME_H
#include "../classes/Scene.h"
#include "../classes/Settings.h"
#include "../classes/SceneManager.h"
#include "../classes/UI/Menu.h"

class OnlineGame : public Scene {
public:
    OnlineGame(sf::RenderWindow
    &window,
    Settings &settings, SceneManager
    &sceneManager);

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
    Menu menu;
    int timer = 0;

    void reconstructMenu();

    bool menu_event;
};


#endif //CHECKERS_ONLINEGAME_H
