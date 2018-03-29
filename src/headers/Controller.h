//
// Created by wint3rmute on 3/6/18.
//

#ifndef PROJECT_CONTROLLER_H
#define PROJECT_CONTROLLER_H


#include "Plane.h"

class Controller {
protected:
    Plane * controlledPlane;

public:
    bool wasRemoved = false;
    explicit Controller(Plane * plane);
    virtual void control() = 0;
};


#endif //PROJECT_CONTROLLER_H
