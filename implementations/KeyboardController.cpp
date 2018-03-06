//
// Created by wint3rmute on 3/6/18.
//

#include "../headers/KeyboardController.h"


KeyboardController::KeyboardController(Plane *plane) : Controller(plane) {
    turn_left_key = sf::Keyboard::Left;
    turn_right_key = sf::Keyboard::Right;
    shoot_key = sf::Keyboard::Down;
    boost_key = sf::Keyboard::Up;
}

void KeyboardController::changeKeys(Key new_left, Key new_right, Key new_shoot, Key new_boost) {
    turn_left_key = new_left;
    turn_right_key = new_right;
    shoot_key = new_shoot;
    boost_key = new_boost;

}

void KeyboardController::control() {

    if(isPressed(turn_left_key)) {

        controlledPlane->turn(LEFT);

    } else if(isPressed(turn_right_key)) {

        controlledPlane->turn(RIGHT);

    }

    if(isPressed(shoot_key)) {

        controlledPlane->shoot();

    }

}
