//
// Created by valen on 5/4/2023.
//

#include "Menu.h"

/* TODO: переробити все */

/**
 * Додає Label до меню
 * @param label - вказівник на Label
 */
void Menu::addLabel(Label *label) {
    labels.push_back(label);
}

/**
 * Додає Button до меню
 * @param button - вказівник на Button
 */
void Menu::addButton(Button *button) {
    buttons.push_back(button);
}

/**
 * Малює всі Label та Button
 */
void Menu::draw() {
    for (auto button: buttons) {
        button->draw();
    }
    for (auto label: labels) {
        label->draw();
    }
}

/**
 * Оновлює всі Button
 * @param mouse_position - позиція миші
 */
void Menu::update(sf::Vector2<float> mouse_position) {
    for (auto button: buttons) {
        button->update(mouse_position);
    }
}

/**
 * Очищує всі Button
 */
void Menu::clearButtons() {
    //free
    for (auto button: buttons) {
        delete button;
    }

    buttons.clear();
}

/**
 * Очищує всі Label
 */
void Menu::clearLabels() {
    //free
    for (auto label: labels) {
        delete label;
    }
    labels.clear();
}

/**
 * Повертає Label за індексом
 * @param index - індекс
 * @return - вказівник на Label
 */
Label *Menu::getLabel(int index) {
    return labels[index];
}

/**
 * Очищує всі Label та Button
 */
void Menu::clear() {
    clearButtons();
    clearLabels();
}

