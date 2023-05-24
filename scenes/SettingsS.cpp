//
// Created by valen on 5/5/2023.
//

#include <iostream>
#include "SettingsS.h"

SettingsS::SettingsS(sf::RenderWindow &window, Settings &settings, SceneManager &sceneManager) {
    this->window = &window;
    this->settings = &settings;
    this->sceneManager = &sceneManager;
}

void SettingsS::update(int deltaTime) {
    if (menu_event) {
        menu_event = false;
        menu.update(sf::Vector2f(sf::Mouse::getPosition(*window)));
    }
}

void SettingsS::back_onClick() {
    sceneManager->switchToScene(0);
}

void onClick(void *cat) {
    ((SettingsS *) cat)->back_onClick();
}

void SettingsS::reconstructMenu() {
    menu.clearButtons();
    menu.clearLabels();
    menu.addButton(new Button(*window, "Back", sf::Vector2f(window->getSize().x / 2,
                                                            window->getSize().y / 1.2), this, ::onClick));
    menu.addLabel(new Label(sf::Vector2f(window->getSize().x / 8, window->getSize().y / 19), "Settings", *window, window->getSize().y / 17));
}

void SettingsS::draw(sf::RenderWindow &target) {
    menu.draw();
}

void SettingsS::handleEvent(const sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            sceneManager->switchToScene(0);
        }
    }
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            sceneManager->switchToScene(0);
        }
    }
    if (event.type == sf::Event::Resized) {
        sf::FloatRect visibleArea(0.f, 0.f, (float) event.size.width, (float) event.size.height);
        window->setView(sf::View(visibleArea));
        reconstructMenu();
    }
    menu_event = true;
}

void SettingsS::onEnter() {
    std::cout << "SettingsS::onEnter()" << std::endl;
    reconstructMenu();
}

void SettingsS::onExit() {
    std::cout << "SettingsS::onExit()" << std::endl;
}
