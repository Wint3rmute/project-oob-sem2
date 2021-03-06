//
// Created by wint3rmute on 3/6/18.
//

#ifndef PROJECT_KEYBOARDCONTROLLER_H
#define PROJECT_KEYBOARDCONTROLLER_H


#include "Controller.h"
#define Key sf::Keyboard::Key
#define isPressed sf::Keyboard::isKeyPressed

/**
 * @brief Uses a keyboard input to move the plane around
 */
class KeyboardController : public Controller {

    /**
     * @name 
     */
    ///@{
    Key turnLeftKey;
    Key turnRightKey;
    Key shootKey;
    Key boostKey;
    ///@}

public:
    explicit KeyboardController(Plane *plane);
    void changeKeys(Key new_left, Key new_right, Key new_shoot, Key new_boost);
    void control();
};


#endif //PROJECT_KEYBOARDCONTROLLER_H
