//
// Created by wint3rmute on 3/6/18.
//

#ifndef PROJECT_CONTROLLER_H
#define PROJECT_CONTROLLER_H


#include "Plane.h"
#include "FieldOfView.h"
class FieldOfView;

class Controller {
protected:
    Plane * controlledPlane;

public:
    bool wasRemoved = false;
    FieldOfView * fieldOfView;
    explicit Controller(Plane * plane);
    virtual void control() = 0;
};


#endif //PROJECT_CONTROLLER_H
