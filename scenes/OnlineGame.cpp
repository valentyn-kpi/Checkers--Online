//
// Created by valen on 5/21/2023.
//

#include "OnlineGame.h"

OnlineGame::OnlineGame(sf::RenderWindow &window, Settings &settings, SceneManager &sceneManager) {
    this->window = &window;
    this->settings = &settings;
    this->sceneManager = &sceneManager;
}

void OnlineGame::update(int deltaTime) {
    if (menu_event) {
        menu_event = false;
        menu.update(sf::Vector2f(sf::Mouse::getPosition(*window)));
    }
}

void OnlineGame::draw(sf::RenderWindow &target) {
    menu.draw();
}

void OnlineGame::handleEvent(const sf::Event &event) {
    if (event.type == sf::Event::Resized) {
        sf::FloatRect visibleArea(0.f, 0.f, (float) event.size.width, (float) event.size.height);
        window->setView(sf::View(visibleArea));
        reconstructMenu();
    }
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            sceneManager->switchToScene(0);
        }
    }
    menu_event = true;
}

void OnlineGame::back_onClick() {
    sceneManager->switchToScene(0);
}

void mainMenu_onClick(void *thouse) {
    ((OnlineGame *) thouse)->back_onClick();
}

void OnlineGame::reconstructMenu() {
    menu.clear();
    menu.addButton(new Button(*window, "Back", sf::Vector2f(window->getSize().x / 2,
                                                            window->getSize().y / 1.2), this, ::mainMenu_onClick));
    menu.addLabel(new Label(sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2.1), "Sorry, online gameplay is not implemented yet :( \nBut will be soon :)", *window, window->getSize().y / 21));
}

void OnlineGame::onEnter() {
    reconstructMenu();
}

void OnlineGame::onExit() {

}

