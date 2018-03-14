//
// Created by wint3rmute on 3/6/18.
//

#include "../headers/KeyboardController.h"


KeyboardController::KeyboardController(Plane *plane) : Controller(plane) {
    turnLeftKey = sf::Keyboard::Left;
    turnRightKey = sf::Keyboard::Right;
    shootKey = sf::Keyboard::Down;
    boostKey = sf::Keyboard::Up;
}

void KeyboardController::changeKeys(Key new_left, Key new_right, Key new_shoot, Key new_boost) {
    turnLeftKey = new_left;
    turnRightKey = new_right;
    shootKey = new_shoot;
    boostKey = new_boost;

}

void KeyboardController::control() {

    if(isPressed(turnLeftKey)) {

        controlledPlane->turn(LEFT);

    } else if(isPressed(turnRightKey)) {

        controlledPlane->turn(RIGHT);

    }

    if(isPressed(shootKey)) {

        controlledPlane->shoot();

    }

}
