//
// Created by wint3rmute on 3/6/18.
//

#include "../headers/Controller.h"

Controller::Controller(Plane * plane) {
    controlledPlane = plane;
    plane->setController(this);
}
