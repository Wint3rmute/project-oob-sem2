//
// Created by wint3rmute on 3/6/18.
//

#ifndef PROJECT_KEYBOARDCONTROLLER_H
#define PROJECT_KEYBOARDCONTROLLER_H


#include "Controller.h"
#define Key sf::Keyboard::Key
#define isPressed sf::Keyboard::isKeyPressed

class KeyboardController : public Controller {

    Key turn_left_key;
    Key turn_right_key;
    Key shoot_key;
    Key boost_key;


public:
    explicit KeyboardController(Plane *plane);
    void changeKeys(Key new_left, Key new_right, Key new_shoot, Key new_boost);
    void control();
};


#endif //PROJECT_KEYBOARDCONTROLLER_H
