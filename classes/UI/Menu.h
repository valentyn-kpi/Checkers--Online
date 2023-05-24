//
// Created by valen on 5/4/2023.
//

#ifndef CHECKERS_MENU_H
#define CHECKERS_MENU_H
#include "Label.h"
#include "Button.h"
#include <vector>

/**
 * Клас Menu об'єктами якого є меню
 */
class Menu {
public:
    void addLabel(Label *label);
    void addButton(Button *button);

    Label *getLabel(int index);

    void clearButtons();
    void clearLabels();

    void update(sf::Vector2<float> mouse_position);
    void draw();

    void clear();

private:
    std::vector<Label*> labels;
    std::vector<Button*> buttons;
};

#endif //CHECKERS_MENU_H
