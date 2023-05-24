//
// Created by valen on 5/5/2023.
//

#ifndef CHECKERS_SETTINGSS_H
#define CHECKERS_SETTINGSS_H
#include "../classes/Scene.h"
#include "../classes/Settings.h"
#include "../classes/SceneManager.h"
#include "../classes/UI/Menu.h"

class SettingsS : public Scene {
public:
    SettingsS(sf::RenderWindow &window, Settings &settings, SceneManager &sceneManager);

    void update(int deltaTime) override;

    void draw(sf::RenderWindow &target) override;

    void handleEvent(const sf::Event &event) override;

    void onEnter() override;

    void onExit() override;

    void back_onClick();

private:
    sf::RenderWindow *window;
    Settings *settings;
    Menu menu;
    SceneManager *sceneManager;
    bool menu_event = true;

    void reconstructMenu();

};


#endif //CHECKERS_SETTINGSS_H
