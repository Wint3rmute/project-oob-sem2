//
// Created by wint3rmute on 3/8/18.
//

#ifndef PROJECT_DUMMYCONTROLLER_H
#define PROJECT_DUMMYCONTROLLER_H


#include "Controller.h"

/**
 * @brief Testing controller
 * This controlled can be used for testing only
 *
 * all it does is turning left and shooting all the time
 */
class DummyController : public Controller{

public:
    /**
     * Controller constructor
     * @param plane plane that is controlled by it
     */
    DummyController(Plane * plane);
    /**
     * @brief Controller behaviour
     * All it does is sending signals to plane
     * to turn and shoot
     */
    void control();

};


#endif //PROJECT_DUMMYCONTROLLER_H
