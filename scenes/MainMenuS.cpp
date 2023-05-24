//
// Created by valen on 5/4/2023.
//

#include <iostream>
#include "MainMenuS.h"

MainMenuS::MainMenuS(sf::RenderWindow &window, Settings &settings, SceneManager &sceneManager) {
    this->window = &window;
    this->settings = &settings;
    this->sceneManager = &sceneManager;
}

void MainMenuS::startOfflineGame() {
    sceneManager->switchToScene(1);
}

void MainMenuS::startOnlineGame() {
    sceneManager->switchToScene(4);
}

void MainMenuS::openSettings() {
    sceneManager->switchToScene(2);
}

void MainMenuS::openAbout() {
    sceneManager->switchToScene(3);
}

void MainMenuS::exitGame() {
    window->close();
}

void offline_onClick(void *cat) {
    auto *menu = (MainMenuS *) cat;
    menu->startOfflineGame();
}

void online_onClick(void *cat) {
    auto *menu = (MainMenuS *) cat;
    menu->startOnlineGame();
}

void settings_onClick(void *cat) {
    auto *menu = (MainMenuS *) cat;
    menu->openSettings();
}

void about_onClick(void *cat) {
    auto *menu = (MainMenuS *) cat;
    menu->openAbout();
}

void exit_onClick(void *cat) {
    auto *menu = (MainMenuS *) cat;
    menu->exitGame();
}


void MainMenuS::draw(sf::RenderWindow &target) {
    target.draw(*renderSprite);
    scene_menu.draw();
}

void MainMenuS::renderBoard() {
    delete renderTexture;
    renderTexture = new sf::RenderTexture();

    float size = 1.2f * (float) std::max(window->getSize().x, window->getSize().y);
    renderTexture->create(size, size);
    renderTexture->setSmooth(true);
    renderTexture->clear(sf::Color::Transparent);

    delete gameBoard;
    gameBoard = new GameBoard(*renderTexture);

    gameBoard->draw();
    renderTexture->display();

    delete renderSprite;
    renderSprite = new sf::Sprite(renderTexture->getTexture());

    renderSprite->setOrigin(renderSprite->getLocalBounds().width / 2.0f, renderSprite->getLocalBounds().height / 2.0f);
    renderSprite->setPosition(window->getSize().x / 2.0f, window->getSize().y / 2.0f);
    renderSprite->setColor(sf::Color(100, 100, 100));
}

void MainMenuS::reconstructMenu() {
    renderBoard();
    scene_menu.clearButtons();
    scene_menu.clearLabels();

    float size_x = (float) window->getSize().x;
    float size_y = (float) window->getSize().y;

    auto *title = new Label(sf::Vector2f(size_x / 2.0f, size_y / 6.0f), "Checkers::Online", *window, std::min(size_x, size_y) / 10.0f);
    scene_menu.addLabel(title);

    auto *play_b = new Button(*window, "Play offline", sf::Vector2f(size_x / 2.0f, size_y / 3.0f), this, offline_onClick);
    scene_menu.addButton(play_b);

    auto *play_online = new Button(*window, "Online",
                       sf::Vector2f(size_x / 2.0f, play_b->getPosition().y + 2.0f * play_b->getCharterSize()), this, online_onClick);
    scene_menu.addButton(play_online);

    auto *settings_b = new Button(*window, "Settings",
                      sf::Vector2f(size_x / 2.0f, play_online->getPosition().y + 2.0f * play_online->getCharterSize()), this, settings_onClick);
    scene_menu.addButton(settings_b);

    auto *about_b = new Button(*window, "About",
                   sf::Vector2f(size_x / 2.0f, settings_b->getPosition().y + 2.0f * settings_b->getCharterSize()), this, about_onClick);
    scene_menu.addButton(about_b);

    auto *exit_b = new Button(*window, "Exit",
                  sf::Vector2f(size_x / 2.0f, about_b->getPosition().y + 2.0f * about_b->getCharterSize()), this, exit_onClick);
    scene_menu.addButton(exit_b);
}

void MainMenuS::handleEvent(const sf::Event &event) {
    if (event.type == sf::Event::Resized) {
        sf::FloatRect visibleArea(0.f, 0.f, (float) event.size.width, (float) event.size.height);
        window->setView(sf::View(visibleArea));
        reconstructMenu();
    }
    menu_event = true;
}

void MainMenuS::update(int deltaTime) {
    timer += deltaTime;
    if (menu_event) {
        menu_event = false;
        scene_menu.update(sf::Vector2f(sf::Mouse::getPosition(*window)));
    }
    if (timer > 50) {
        renderSprite->rotate(0.2f);
    }
}

void MainMenuS::onEnter() {
    std::cout << "MainMenuS::onEnter()" << std::endl;
    renderTexture = nullptr;
    renderSprite = nullptr;
    gameBoard = nullptr;
    reconstructMenu();
}

void MainMenuS::onExit() {
    std::cout << "MainMenuS::onExit()" << std::endl;
    delete gameBoard;
    delete renderTexture;
    delete renderSprite;
}

