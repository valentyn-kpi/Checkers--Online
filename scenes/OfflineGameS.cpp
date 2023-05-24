//
// Created by valen on 5/5/2023.
//

#include <iostream>
#include "OfflineGameS.h"

OfflineGameS::OfflineGameS(sf::RenderWindow &window, Settings &settings, SceneManager &sceneManager) {
    this->window = &window;
    this->settings = &settings;
    this->sceneManager = &sceneManager;
}

void OfflineGameS::update(int deltaTime) {
    if (menu_event) {
        menu_event = false;
        menu.update(sf::Vector2f(sf::Mouse::getPosition(*window)));
        switch (gameBoard->getGameState()) {
            case GameBoard::RED_TURN: {
                menu.getLabel(0)->setText("White moves");
                break;
            }
            case GameBoard::BLACK_TURN: {
                menu.getLabel(0)->setText("Black moves");
                break;
            }
            case GameBoard::RED_WON: {
                menu.getLabel(0)->setText("White won");
                break;
            }
            case GameBoard::BLACK_WON: {
                menu.getLabel(0)->setText("Black won");
                break;
            }
            case GameBoard::DRAW: {
                menu.getLabel(0)->setText("Draw");
                break;
            }
        }
        menu.getLabel(1)->setText("White: " + std::to_string(gameBoard->getPieceCount(GameBoard::RED_C)) +
                                 "\nBlack: " + std::to_string(gameBoard->getPieceCount(GameBoard::BLACK_C)));
    }
}

void OfflineGameS::draw(sf::RenderWindow &target) {
    if (gameBoard != nullptr)
        gameBoard->draw();
    menu.draw();
}

void OfflineGameS::back_onClick() {
    sceneManager->switchToScene(0);
}

void back_onClick(void *cat) {
    ((OfflineGameS *) cat)->back_onClick();
}

void OfflineGameS::reconstructMenu() {
    menu.clearButtons();
    menu.clearLabels();
    sf::Vector2f windowSize = window->getView().getSize();

    const int size = std::min(windowSize.x - gameBoard->getBoardSize().x, windowSize.y);

    menu.addButton(new Button(*window, "Back", sf::Vector2f(gameBoard->getBoardSize().x + (windowSize.x - gameBoard->getBoardSize().x) / 2,
                                                              windowSize.y / 1.2), this, ::back_onClick));
    menu.addLabel(new Label(sf::Vector2f(gameBoard->getBoardSize().x + (windowSize.x - gameBoard->getBoardSize().x) / 2,
                                     windowSize.y / 12), "%%", *window, size / 8));

    menu.addLabel(new Label(sf::Vector2f(gameBoard->getBoardSize().x + (windowSize.x - gameBoard->getBoardSize().x) / 2,
                                     windowSize.y / 4), "%%", *window, size / 12));
    std::cout << "OfflineGameS::reconstructMenu() end" << std::endl << std::flush;
}

void OfflineGameS::handleEvent(const sf::Event &event) {
    if (gameBoard != nullptr) gameBoard->handleEvent(event);
    if (event.type == sf::Event::Resized) {
        sf::FloatRect visibleArea(0.f, 0.f, (float) event.size.width, (float) event.size.height);
        window->setView(sf::View(visibleArea));
        reconstructMenu();
    }
    menu_event = true;
}

void OfflineGameS::onEnter() {
    menu_event = true;
    gameBoard = new GameBoard(*window);
    reconstructMenu();
}

void OfflineGameS::onExit() {
    delete gameBoard;
}