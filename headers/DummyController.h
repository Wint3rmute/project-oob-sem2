//
// Created by wint3rmute on 3/8/18.
//

#ifndef PROJECT_DUMMYCONTROLLER_H
#define PROJECT_DUMMYCONTROLLER_H


#include "Controller.h"

class DummyController : public Controller{

public:
    DummyController(Plane * plane);
    void control();

};


#endif //PROJECT_DUMMYCONTROLLER_H
