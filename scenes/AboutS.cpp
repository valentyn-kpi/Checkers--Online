//
// Created by valen on 5/5/2023.
//

#include "AboutS.h"

AboutS::AboutS(sf::RenderWindow &window, Settings &settings, SceneManager &sceneManager) {
    this->window = &window;
    this->settings = &settings;
    this->sceneManager = &sceneManager;
    menu_event = true;
}

void AboutS::update(int deltaTime) {
    if (menu_event) {
        menu_event = false;
        menu.update(sf::Vector2f(sf::Mouse::getPosition(*window)));
    }
}

void AboutS::draw(sf::RenderWindow &target) {
    menu.draw();
}

void AboutS::Back_onClick() {
    sceneManager->switchToScene(0);
}

void bonClick(void *data) {
    ((AboutS *) data)->Back_onClick();
}

void AboutS::reconstructMenu() {
    menu.clearButtons();
    menu.clearLabels();
    menu.addButton(new Button(*window, "Back", sf::Vector2f(window->getSize().x / 2,
                                                            window->getSize().y / 1.2), this, ::bonClick));
    menu.addLabel(new Label(sf::Vector2f(window->getSize().x / 10, window->getSize().y / 20), "About", *window, window->getSize().y / 17));
    menu.addLabel(new Label(sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2.2), "\tGame 'Checkers::Online' is in development by Valentyn Valentiev\n"
                                                                                                                       "as an University project. \n"
                                                                                                                       "The game is written in C++ using SFML library.\n\n"
                                                                                                                       "\tPS: you can figure out the rules of the game by yourself.\n\n"
                                                                                                                     "TODO: \n"
                                                                                                                     "\t1. Redo UI (crate parent class UI and sub classes Button,\n"
                                                                                                                     "TextBox, Label etc)\n"
                                                                                                                     "\t2. Implement client and server for online gameplay\n"
                                                                                                                     "\t3. Implement Settings scene\n"
                                                                                                                     "\t3. Improve visual look\n"
                                                                                                                     "\t4. Redo Button function (do with 1)", *window, window->getSize().y / 28));
}


void AboutS::handleEvent(const sf::Event &event) {
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

void AboutS::onEnter() {
    reconstructMenu();
}

void AboutS::onExit() {

}
