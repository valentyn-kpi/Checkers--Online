//
// Created by valen on 5/5/2023.
//

#ifndef CHECKERS_ABOUTS_H
#define CHECKERS_ABOUTS_H

#include "../classes/Scene.h"
#include "../classes/Settings.h"
#include "../classes/SceneManager.h"
#include "../classes/UI/Menu.h"

class AboutS : public Scene {
public:
    AboutS(sf::RenderWindow
    &window,
    Settings &settings, SceneManager
    &sceneManager);

    void update(int deltaTime) override;

    void draw(sf::RenderWindow &target) override;

    void handleEvent(const sf::Event &event) override;

    void onEnter() override;

    void onExit() override;

    void Back_onClick();

private:
    SceneManager *sceneManager;
    sf::RenderWindow *window;
    Settings *settings;
    sf::Text text;
    Menu menu;
    int timer = 0;

    void reconstructMenu();

    bool menu_event;
};


#endif //CHECKERS_ABOUTS_H
