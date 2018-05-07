//
// Created by wint3rmute on 3/8/18.
//

#ifndef PROJECT_DUMMYCONTROLLER_H
#define PROJECT_DUMMYCONTROLLER_H


#include "Controller.h"

/*
 * This controlled can be used for testing only
 *
 * all it does is turning left and shooting all the time
 */
class DummyController : public Controller{

public:
    DummyController(Plane * plane);
    void control();

};


#endif //PROJECT_DUMMYCONTROLLER_H
